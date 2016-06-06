#include <systems/player_seeking_system.h>

using namespace Halley;

class PlayerSeekingSystem final : public PlayerSeekingSystemBase<PlayerSeekingSystem> {
public:
	void update(Halley::Time, MainFamily& entity)
	{
		// Go through every player, and find the closest one
		Vector2f myPos = entity.position->position;
		Vector2f bestTarget = myPos;
		float bestDistSqr = 2000 * 2000;
		for (auto& p : playersFamily) {
			Vector2f pos = p.position->position;
			float distSqr = (pos - myPos).squaredLength();
			if (distSqr < bestDistSqr) {
				bestDistSqr = distSqr;
				bestTarget = pos;
			}
		}

		// Seek on that player
		Vector2f target = bestTarget - myPos;
		if (target.length() > 1) {
			entity.mob->moveDir = entity.mob->faceDir = target.unit();
		} else {
			entity.mob->moveDir = Vector2f();
		}
	}
};

REGISTER_SYSTEM(PlayerSeekingSystem)
