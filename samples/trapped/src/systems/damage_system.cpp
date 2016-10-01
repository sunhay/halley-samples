#include <systems/damage_system.h>
#include <messages/damage_message.h>

class DamageSystem final : public DamageSystemBase<DamageSystem> {
public:
	void update(Halley::Time time, MainFamily& e) {
		// TODO
	}

	void onMessageReceived(const DamageMessage& msg, MainFamily& entity) {
		int& health = entity.health.current;
		health -= msg.amount;

		if (health <= 0) {
			sendMessage(entity.entityId, DeathMessage());
			health = 0;
			getWorld().destroyEntity(entity.entityId);
		}
	}
};

REGISTER_SYSTEM(DamageSystem)

