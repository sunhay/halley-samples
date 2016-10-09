#include "game_stage.h"
#include "registry.h"
#include <components/position_component.h>
#include <components/velocity_component.h>
#include <components/sprite_component.h>
#include <components/sprite_animation_component.h>
#include <components/mob_component.h>
#include <components/player_input_component.h>
#include <components/player_component.h>
#include <components/shooter_component.h>
#include <components/gun_component.h>
#include <components/collider_component.h>
#include <components/repulse_field_component.h>
#include <components/enemy_spawner_component.h>

using namespace Halley;

void GameStage::init()
{
	world = createWorld("trapped_game_world", createSystem);
	statsView = std::make_unique<WorldStatsView>(*getAPI().core, *world);

	createPlayer(Vector2f(350, 350));

	createBackground();
	createWalls();

	auto devices = getAudioAPI().getAudioDevices();
	getAudioAPI().startPlayback();
	getAudioAPI().playMusic(getResource<AudioClip>("music/talbot.ogg"), 0, 2.0f);
}

void GameStage::deInit()
{

}

void GameStage::onVariableUpdate(Halley::Time t)
{
	world->step(TimeLine::VariableUpdate, t);

	if (getInputAPI().getKeyboard()->isButtonPressed(Keys::Z)) {
		getAudioAPI().stopAllMusic(1.0f);
		getAudioAPI().playMusic(getResource<AudioClip>("music/transi.ogg"), 0, 1.0f);
	}
}

void GameStage::onFixedUpdate(Time t)
{
	world->step(TimeLine::FixedUpdate, t);
}

void GameStage::onRender(RenderContext& context) const
{
	Vector2f playerPos = world->getEntity(playerId).getComponent<PositionComponent>()->position;
	getAudioAPI().setListener(AudioListenerData(Vector3f(playerPos)));
	Camera cam(playerPos, Vector2f(1280, 720));

	context.with(cam).bind([&] (Painter& painter)
	{
		painter.clear(Colour(0, 0, 0));
		world->render(painter);
	});

	if (getAPI().input->getKeyboard()->isButtonDown(Keys::Space)) {
		statsView->draw(context);
	}
}

void GameStage::createPlayer(Vector2f pos) {
	auto& inputApi = getAPI().input;
	auto keyboard = inputApi->getKeyboard(0);

	auto input = std::make_shared<InputVirtual>(0, 4);
	input->bindAxisButton(0, keyboard, Keys::A, Keys::D);
	input->bindAxisButton(1, keyboard, Keys::W, Keys::S);
	input->bindAxisButton(2, keyboard, Keys::Left, Keys::Right);
	input->bindAxisButton(3, keyboard, Keys::Up, Keys::Down);

	auto pl = world->createEntity()
		.addComponent(PositionComponent(pos))
		.addComponent(VelocityComponent(Vector2f(0, 0), Vector2f()))
		.addComponent(SpriteAnimationComponent(AnimationPlayer(getResource<Animation>("ella"))))
		.addComponent(SpriteComponent(Sprite(), 0))
		.addComponent(MobComponent(Vector2f(), Vector2f(), 50, 300))
		.addComponent(PlayerInputComponent(input))
		.addComponent(PlayerComponent())
		.addComponent(ShooterComponent(false, Vector2f(), 0))
		.addComponent(GunComponent(0.1f, "machinegun"))
		.addComponent(ColliderComponent(Rect4f(-13, -13, 26, 26), 0, false, false))
		.addComponent(RepulseFieldComponent(10));

	playerId = pl.getEntityId();
}

void GameStage::createObstacle(Rect4f rect)
{
	Vector2f size = rect.getSize();
	world->createEntity()
		.addComponent(PositionComponent(rect.getCenter()))
		.addComponent(ColliderComponent(Rect4f(-size/2, size/2), 1, false, true));
}

void GameStage::createRoom(Vector2f pos, int id)
{
	world->createEntity()
		.addComponent(PositionComponent(pos + Vector2f(350.0f, 350.0f)))
		.addComponent(SpriteComponent(Sprite()
			.setSprite(getResources(), "trapped_scenery.json", "BG_0" + toString(id + 1) + ".png")
			.setPivot(Vector2f(0.5f, 0.5f))
		, -20));

	auto& rng = Random::getGlobal();

	// Enemy spawners
	float x0 = 125;
	float x1 = 565;
	float y0 = 220;
	float y1 = 605;
	Vector2f spawners[] = { Vector2f(x1, y1), Vector2f(x0, y1), Vector2f(x1, y0), Vector2f(x0, y0) };
	for (Vector2f spawnerPos : spawners) {
		world->createEntity()
			.addComponent(PositionComponent(pos + spawnerPos))
			.addComponent(EnemySpawnerComponent(rng.getFloat(2.0f, 4.0f), id));
	}
}

Vector2f GameStage::getRoomOffset(int i) const
{
	switch (i) {
	case 0: return Vector2f(0, 0);
	case 1: return Vector2f(700, 0);
	case 2: return Vector2f(0, 700);
	case 3: return Vector2f(700, 700);
	}
	return Vector2f();
}

void GameStage::createBackground()
{
	for (int i = 0; i<4; i++) {
		createRoom(getRoomOffset(i), i);
	}

	// Ouroboros
	world->createEntity()
		.addComponent(PositionComponent(Vector2f(700.0f, 752.0f)))
		.addComponent(SpriteComponent(Sprite()
			.setSprite(getResources(), "trapped_scenery.json", "Ouroboros.png")
			.setPivot(Vector2f(0.5f, 0.5f))
			, -25));
}

void GameStage::createWalls()
{
	Rect4f rects[] = {
		Rect4f(0, 0, 1400, 12),
		Rect4f(0, 0, 50, 1400),

		Rect4f(0, 1290, 1400, 50),
		Rect4f(1350, 0, 50, 1400),

		Rect4f(650, 0, 100, 270),
		Rect4f(650, 345, 100, 645),
		Rect4f(650, 1050, 100, 352),

		Rect4f(0, 560, 272, 130),
		Rect4f(460, 560, 500, 130),
		Rect4f(1145, 560, 270, 130)
	};

	for (auto& r : rects) {
		// Rects are from Halley 1, which is upside-down... convert.
		Rect4f r2(r.getLeft(), 1400 - r.getTop() - r.getHeight(), r.getWidth(), r.getHeight());
		createObstacle(r2);
	}
}
