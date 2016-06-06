#include "systems/movement_system.h"

class MovementSystem final : public MovementSystemBase<MovementSystem> {
public:
	void update(Halley::Time time, MainFamily& e)
	{
		e.position->position = e.velocity->targetPosition;
	}
};

REGISTER_SYSTEM(MovementSystem)
