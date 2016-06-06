#include <systems/ttl_system.h>

class TTLSystem final : public TTLSystemBase<TTLSystem> {
public:
	void update(Halley::Time t, MainFamily& entity)
	{
		entity.tTL->timeLeft -= float(t);
		if (entity.tTL->timeLeft <= 0) {
			getWorld().destroyEntity(entity.entityId);
		}
	}
};

REGISTER_SYSTEM(TTLSystem)
