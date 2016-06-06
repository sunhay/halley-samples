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
	void update(Time) {
		if (mainFamily.count() < 10) {
			auto& r = Random::getGlobal();
			createEnemy(Vector2f(r.getFloat(0.0f, 1280.0f), r.getFloat(0.0f, 720.0f)));
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

