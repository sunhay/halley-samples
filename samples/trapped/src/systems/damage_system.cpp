#include <systems/damage_system.h>

class DamageSystem final : public DamageSystemBase<DamageSystem> {
public:
	void update(Halley::Time time, MainFamily& e) {
		// TODO
	}

	void onMessageReceived(const CollisionMessage& msg, MainFamily& entity) {
		// TODO
	}
};

REGISTER_SYSTEM(DamageSystem)

