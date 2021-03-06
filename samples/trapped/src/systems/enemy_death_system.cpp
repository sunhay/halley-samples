#include <systems/enemy_death_system.h>

using namespace Halley;

class EnemyDeathSystem final : public EnemyDeathSystemBase<EnemyDeathSystem> {
public:
	void update(Time time, MainFamily& e) {}
	
	void onMessageReceived(const DeathMessage& msg, MainFamily& entity) {
		String clip = Random::getGlobal().getInt(0, 1) == 0 ? "sound/kill1.ogg" : "sound/kill2.ogg";
		getAPI().audio->play(getAPI().getResource<AudioClip>(clip), AudioSourcePosition::makePositional(entity.position.position));
	}
};

REGISTER_SYSTEM(EnemyDeathSystem)

