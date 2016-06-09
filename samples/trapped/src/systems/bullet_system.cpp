#include <systems/bullet_system.h>

class BulletSystem final : public BulletSystemBase<BulletSystem> {
public:
	void update(Halley::Time, MainFamily&) {
	}
	
	void onMessageReceived(const CollisionMessage& msg, MainFamily& entity) {
		if (msg.otherLayer != 0) {
			getWorld().destroyEntity(entity.entityId);
		}

		// Hit enemy
		if (msg.otherLayer == 1) {
			sendMessage(msg.other, DamageMessage(entity.bullet.damage));
		}
	}
};

REGISTER_SYSTEM(BulletSystem)

