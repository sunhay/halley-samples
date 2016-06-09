#include <systems/integrate_velocity_system.h>

class IntegrateVelocitySystem final : public IntegrateVelocitySystemBase<IntegrateVelocitySystem> {
public:
	void update(Halley::Time time, MainFamily& e)
	{
		e.velocity.targetPosition = e.position.position + e.velocity.velocity * time;
	}
};

REGISTER_SYSTEM(IntegrateVelocitySystem)

