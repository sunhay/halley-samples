#include "game_stage.h"
#include "registry.h"

using namespace Halley;

void GameStage::init()
{
	world = createWorld("game_world", createSystem);
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
		painter.clear(Colour(0.05f, 0.05f, 0.05f));
		world->render(painter);
	});

	if (getAPI().input->getKeyboard()->isButtonDown(Keys::Esc)) {
		getAPI().core->quit();
	}
}

