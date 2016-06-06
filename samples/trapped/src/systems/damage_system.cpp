#include <systems/damage_system.h>

class DamageSystem final : public DamageSystemBase<DamageSystem> {
public:
	void update(Halley::Time p, MainFamily& entity) {
		
	}
};

REGISTER_SYSTEM(DamageSystem)

