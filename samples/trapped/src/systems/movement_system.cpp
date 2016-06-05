#include "systems/movement_system.h"

class MovementSystem final : public MovementSystemBase<MovementSystem> {
public:
	void update(Halley::Time time, MainFamily& e)
	{
		auto& pos = e.position->position;
		auto& vel = e.velocity->velocity;

		pos += vel * time;
	}
};

REGISTER_SYSTEM(MovementSystem)
