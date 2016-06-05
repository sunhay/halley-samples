#include <systems/mob_system.h>

class MobSystem final : public MobSystemBase<MobSystem> {
public:
	void update(Halley::Time p, MainFamily& entity)
	{
		auto dir = entity.mob->moveDir;
		if (dir.squaredLength() > 1) {
			dir = dir.unit();
		}
		entity.velocity->velocity = dir * entity.mob->maxSpeed;
	}
};

REGISTER_SYSTEM(MobSystem)
