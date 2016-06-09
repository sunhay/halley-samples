#include <systems/player_seeking_system.h>
#include <limits>

using namespace Halley;

class PlayerSeekingSystem final : public PlayerSeekingSystemBase<PlayerSeekingSystem> {
public:
	void update(Halley::Time, MainFamily& entity)
	{
		// Find the closest player
		Vector2f myPos = entity.position.position;
		auto bestTarget = Halley::findLowestScore(playersFamily.begin(), playersFamily.end(), std::numeric_limits<float>::max(), [myPos](auto& p) {
			return (p.position.position - myPos).squaredLength();
		});

		if (bestTarget == playersFamily.end()) {
			// No players to seek
			entity.mob.moveDir = Vector2f();
		} else {
			Vector2f target = bestTarget->position.position - myPos;
			entity.mob.moveDir = entity.mob.faceDir = target.unit();
		}
	}
};

REGISTER_SYSTEM(PlayerSeekingSystem)
