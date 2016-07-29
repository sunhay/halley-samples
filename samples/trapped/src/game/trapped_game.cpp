#include "prec.h"
#include "game_stage.h"

using namespace Halley;

void initOpenGLPlugin(IPluginRegistry &registry);

namespace Stages {
	enum Type
	{
		Splash,
		Title,
		Game
	};
}

class TrappedGame final : public Game
{
public:
	int initPlugins(IPluginRegistry &registry) override
	{
		initOpenGLPlugin(registry);
		return HalleyAPIFlags::Video | HalleyAPIFlags::Audio | HalleyAPIFlags::Input;
	}

	void initResourceLocator(String dataPath, ResourceLocator& locator) override
	{
		locator.addFileSystem(dataPath);
	}

	std::unique_ptr<Stage> makeStage(StageID id) override
	{
		switch (id) {
		case Stages::Game:
			return std::make_unique<GameStage>();
		default:
			return std::unique_ptr<Stage>();
		}
	}

	StageID getInitialStage() const override
	{
		return Stages::Game;
	}

	String getName() const override
	{
		return "Trapped: In The Chambers of Eternal Darkness";
	}

	String getDataPath() const override
	{
		return "MiniBoss/Trapped";
	}

	bool isDevBuild() const override
	{
		return true;
	}

	void init(HalleyAPI* api) override
	{
		api->video->setWindow(Window(WindowType::Window, Vector2i(1280, 720), getName(), false));
	}
};

HalleyGame(TrappedGame);
