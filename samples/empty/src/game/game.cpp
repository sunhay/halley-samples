#include "prec.h"
#include "game_stage.h"

using namespace Halley;

void initOpenGLPlugin(IPluginRegistry &registry);
void initSDLPlugin(IPluginRegistry &registry);

class EmptyGame final : public Game
{
public:
	int initPlugins(IPluginRegistry &registry) override
	{
		initSDLPlugin(registry);
		initOpenGLPlugin(registry);
		return HalleyAPIFlags::Video | HalleyAPIFlags::Audio | HalleyAPIFlags::Input;
	}

	void initResourceLocator(String dataPath, ResourceLocator& locator) override
	{
		locator.addFileSystem(dataPath);
	}

	String getName() const override
	{
		return "Empty sample";
	}

	String getDataPath() const override
	{
		return "Halley/EmptySample";
	}

	bool isDevBuild() const override
	{
		return true;
	}

	std::unique_ptr<Stage> startGame(HalleyAPI* api) override
	{
		api->video->setWindow(WindowDefinition(WindowType::Window, Vector2i(1280, 720), getName()), true);
		return std::make_unique<GameStage>();
	}
};

HalleyGame(EmptyGame);
