#include <systems/destroy_on_impact_system.h>

class DestroyOnImpactSystem final : public DestroyOnImpactSystemBase<DestroyOnImpactSystem> {
public:
	void update(Halley::Time time, MainFamily& e) {
	}
	
	void onMessageReceived(const CollisionMessage& msg, MainFamily& entity) {
		getWorld().destroyEntity(entity.entityId);
	}
};

REGISTER_SYSTEM(DestroyOnImpactSystem)

