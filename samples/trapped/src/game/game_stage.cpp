#include "game_stage.h"
#include "registry.h"
#include <components/position_component.h>
#include <components/velocity_component.h>
#include <components/sprite_component.h>
#include <components/sprite_animation_component.h>
#include <components/mob_component.h>
#include <components/player_input_component.h>

using namespace Halley;

void GameStage::init()
{
	world = createWorld("trapped_game_world.yaml", createSystem);
	statsView = std::make_unique<WorldStatsView>(*getAPI().core, *world);

	createPlayer();
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

void GameStage::createPlayer() {
	auto& inputApi = getAPI().input;
	auto keyboard = inputApi->getKeyboard(0);

	auto input = std::make_shared<InputVirtual>(0, 4);
	input->bindAxisButton(0, keyboard, Keys::A, Keys::D);
	input->bindAxisButton(1, keyboard, Keys::W, Keys::S);
	input->bindAxisButton(2, keyboard, Keys::Left, Keys::Right);
	input->bindAxisButton(3, keyboard, Keys::Up, Keys::Down);

	world->createEntity()
		.addComponent(new PositionComponent(Vector2f(640, 360)))
		.addComponent(new VelocityComponent(Vector2f(0, 0)))
		.addComponent(new SpriteAnimationComponent(AnimationPlayer(getResource<Animation>("ella.yaml"))))
		.addComponent(new SpriteComponent())
		.addComponent(new MobComponent(Vector2f(), Vector2f(), 50, 300))
		.addComponent(new PlayerInputComponent(input));
}
