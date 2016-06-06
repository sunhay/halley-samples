#pragma once
#include <type_traits>

#include <halley.hpp>

class GameStage final : public Halley::EntityStage {
public:
	void init() override;
	void deInit() override;

	void onFixedUpdate(Halley::Time) override;
	void onRender(Halley::RenderContext&) const override;

private:
	void createPlayer(Halley::Vector2f pos);
	void createEnemy(Halley::Vector2f pos);

	std::unique_ptr<Halley::World> world;
	std::unique_ptr<Halley::WorldStatsView> statsView;
};

