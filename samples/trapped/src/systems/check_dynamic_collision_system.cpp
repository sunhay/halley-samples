#include <systems/check_dynamic_collision_system.h>

class CheckDynamicCollisionSystem final : public CheckDynamicCollisionSystemBase<CheckDynamicCollisionSystem> {
public:
	void update(Halley::Time time, MainFamily& e) {
		// TODO: make this more efficient

		// Skip static objects
		if (e.collider->isStatic) {
			return;
		}

		auto myRect = e.position->position + e.collider->rect;
		for (auto& o : targetsFamily) {
			// Don't check against static objects, or against myself
			if (!o.collider->isStatic && o.entityId != e.entityId) {
				auto rect = o.position->position + o.collider->rect;
				if (myRect.overlaps(rect)) {
					sendMessage(e.entityId, CollisionMessage(o.entityId, o.collider->layer));
				}
			}
		}
	}
};

REGISTER_SYSTEM(CheckDynamicCollisionSystem)

