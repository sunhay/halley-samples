#include <systems/enemy_spawning_system.h>

#include <components/position_component.h>
#include <components/velocity_component.h>
#include <components/sprite_component.h>
#include <components/sprite_animation_component.h>
#include <components/mob_component.h>
#include <components/enemy_component.h>
#include <components/collider_component.h>
#include <components/health_component.h>
#include <components/repulse_field_component.h>

using namespace Halley;

class EnemySpawningSystem final : public EnemySpawningSystemBase<EnemySpawningSystem> {
public:
	void update(Time time) {
		for (auto& e : mainFamily) {
			e.enemySpawner->cooldown = std::max(0.0f, e.enemySpawner->cooldown - float(time));
		}

		if (enemiesFamily.count() < 10) {
			auto& rng = Random::getGlobal();

			auto eligible = filterRef(mainFamily.begin(), mainFamily.end(), [](MainFamily e) -> bool { return e.enemySpawner->roomId == 0 && e.enemySpawner->cooldown == 0; });
			if (eligible.size() > 0) {
				auto choice = pickRandom(eligible.begin(), eligible.end(), rng).get();

				createEnemy(choice.position->position);
				choice.enemySpawner->cooldown = rng.getFloat(2.0f, 5.0f);
			}
		}
	}

private:
	void createEnemy(Vector2f pos)
	{
		getWorld().createEntity()
			.addComponent(PositionComponent(pos))
			.addComponent(VelocityComponent(Vector2f(0, 0), Vector2f()))
			.addComponent(SpriteAnimationComponent(AnimationPlayer(getAPI().getResource<Animation>("zombies.yaml"), "zombie" + String::integerToString(Random::getGlobal().get(1, 5)))))
			.addComponent(SpriteComponent(Sprite(), 0))
			.addComponent(MobComponent(Vector2f(), Vector2f(), 30, 60))
			.addComponent(EnemyComponent())
			.addComponent(ColliderComponent(Rect4f(-18, -18, 36, 36), 1, false, false))
			.addComponent(HealthComponent(2, 2))
			.addComponent(RepulseFieldComponent(5));
	}
};

REGISTER_SYSTEM(EnemySpawningSystem)

