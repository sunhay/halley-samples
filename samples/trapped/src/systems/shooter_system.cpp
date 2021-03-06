#include <systems/shooter_system.h>
#include <components/position_component.h>
#include <components/velocity_component.h>
#include <components/sprite_component.h>
#include <components/bullet_component.h>
#include <components/ttl_component.h>
#include <components/collider_component.h>

using namespace Halley;

class ShooterSystem final : public ShooterSystemBase<ShooterSystem> {
public:
	void update(Time p, MainFamily& e)
    {
		float& cooldown = e.shooter.cooldown;
		if (cooldown > 0) {
			cooldown = std::max(cooldown - float(p), 0.0f);
		}

        if (e.shooter.shooting && cooldown < 0.01f) {
			cooldown = e.gun.cooldown;
			spawnBullet(e.gun.type, e.position.position, e.shooter.shootDir, e.velocity.velocity);
        }
    }

private:
	void spawnBullet(const String& type, Vector2f pos, Vector2f dir, Vector2f playerVel)
	{
		Vector2f vel = dir * 500 + playerVel * 0.5f;
		Vector2f origin = pos + Vector2f(0, 15) + vel * 0.016f;
		float ttl = 0.4f;
		int damage = 1;

		getWorld().createEntity()
			.addComponent(PositionComponent(origin))
			.addComponent(VelocityComponent(vel, Vector2f()))
			.addComponent(SpriteComponent(Sprite()
				.setSprite(getAPI().core->getResources(), "trapped_sprites", "simple_bullet.png")
				.setColour(Colour(1, 1, 0))
				.setPivot(Vector2f(0.5f, 0.5f))
				.setRotation(vel.angle()), 0))
			.addComponent(BulletComponent(damage))
			.addComponent(TTLComponent(ttl))
			.addComponent(ColliderComponent(Rect4f(-5, -5, 10, 10), 2, false, false));

		auto clip = getAPI().getResource<AudioClip>("sound/weak_shot.ogg");
		getAPI().audio->play(clip, AudioSourcePosition::makePositional(origin));
	}
};

REGISTER_SYSTEM(ShooterSystem)
