#include <systems/flashing_system.h>

using namespace Halley;

class FlashingSystem final : public FlashingSystemBase<FlashingSystem> {
public:
	void update(Time time, MainFamily& e) {
		if (e.flashing.active) {
			if (e.flashing.curTime > e.flashing.totalTime) {
				e.flashing.active = false;
			}
			float t = 1.0f - (e.flashing.curTime / e.flashing.totalTime);
			e.flashing.curTime += float(time);
			e.sprite.sprite.setColour(lerp(Colour4f(1, 1, 1, 1), e.flashing.colour, t));
		} else {
			e.sprite.sprite.setColour(Colour4f(1, 1, 1, 1));
		}
		
	}
	
	void onMessageReceived(const DamageMessage& msg, MainFamily& entity) {
		entity.flashing.colour = Colour4f(2.0f, 1.2f, 1.2f, 1.0f);
		entity.flashing.curTime = 0;
		entity.flashing.totalTime = 0.1f;
		entity.flashing.active = true;
	}
};

REGISTER_SYSTEM(FlashingSystem)

