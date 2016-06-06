#include <systems/shooter_system.h>
#include <components/position_component.h>
#include <components/velocity_component.h>
#include <components/sprite_component.h>
#include <components/bullet_component.h>
#include <components/t_t_l_component.h>

using namespace Halley;

class ShooterSystem final : public ShooterSystemBase<ShooterSystem> {
public:
	void update(Time p, MainFamily& e)
    {
		float& cooldown = e.shooter->cooldown;
		if (cooldown > 0) {
			cooldown = std::max(cooldown - float(p), 0.0f);
		}

        if (e.shooter->shooting && cooldown < 0.01f) {
			cooldown = e.gun->cooldown;
			spawnBullet(e.gun->type, e.position->position, e.shooter->shootDir, e.velocity->velocity);
        }
    }

private:
	void spawnBullet(const String& type, Vector2f pos, Vector2f dir, Vector2f playerVel)
	{
		Vector2f origin = pos + Vector2f(0, -10);
		Vector2f vel = dir * 500 + playerVel * 0.5f;
		float ttl = 0.4f;
		float damage = 1;

		getWorld().createEntity()
			.addComponent(new PositionComponent(origin))
			.addComponent(new VelocityComponent(vel))
			.addComponent(new SpriteComponent(Sprite().setImage(getAPI().core->getResources(), "FX/simple_bullet.png").setColour(Colour(1, 1, 0)).setPivot(Vector2f(0.5f, 0.5f)), 0))
			.addComponent(new BulletComponent(damage))
			.addComponent(new TTLComponent(ttl));
	}
};

REGISTER_SYSTEM(ShooterSystem)
