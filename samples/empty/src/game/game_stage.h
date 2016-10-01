#pragma once
#include <halley.hpp>

class GameStage final : public Halley::EntityStage {
public:
	void init() override;
	void deInit() override;

	void onFixedUpdate(Halley::Time) override;
	void onRender(Halley::RenderContext&) const override;

private:
	std::unique_ptr<Halley::World> world;
};

