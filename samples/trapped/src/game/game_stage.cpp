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

using namespace Halley;

void GameStage::init()
{
	world = createWorld("trapped_game_world.yaml", createSystem);
	statsView = std::make_unique<WorldStatsView>(*getAPI().core, *world);

	createPlayer(Vector2f(640, 360));

	createObstacle(Vector2f(800, 360), Vector2f(100, 100));
	createObstacle(Vector2f(900, 360), Vector2f(100, 400));
}

void GameStage::deInit()
{

}

void GameStage::onFixedUpdate(Time t)
{
	world->step(TimeLine::FixedUpdate, t);
}

void GameStage::onRender(RenderContext& context) const
{
	context.bind([&] (Painter& painter)
	{
		painter.clear(Colour(0.7f, 0.7f, 0.7f));
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

	world->createEntity()
		.addComponent(PositionComponent(pos))
		.addComponent(VelocityComponent(Vector2f(0, 0), Vector2f()))
		.addComponent(SpriteAnimationComponent(AnimationPlayer(getResource<Animation>("ella.yaml"))))
		.addComponent(SpriteComponent(Sprite(), 0))
		.addComponent(MobComponent(Vector2f(), Vector2f(), 50, 300))
		.addComponent(PlayerInputComponent(input))
		.addComponent(PlayerComponent())
		.addComponent(ShooterComponent(false, Vector2f(), 0))
		.addComponent(GunComponent(0.1f, "machinegun"))
		.addComponent(ColliderComponent(Rect4f(-13, -13, 26, 26), 0, false, false))
		.addComponent(RepulseFieldComponent(10));
}

void GameStage::createObstacle(Vector2f pos, Vector2f size)
{
	world->createEntity()
		.addComponent(PositionComponent(pos))
		.addComponent(ColliderComponent(Rect4f(-size/2, size/2), 1, false, true));
}
