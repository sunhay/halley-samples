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

	std::unique_ptr<Stage> startGame(HalleyAPI* api) override
	{
		api->video->setWindow(Window(WindowType::Window, Vector2i(), Vector2i(1280, 720), getName()), true);
		return std::make_unique<GameStage>();
	}
};

HalleyGame(TrappedGame);
