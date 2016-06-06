#include <systems/check_dynamic_collision_system.h>

class CheckDynamicCollisionSystem final : public CheckDynamicCollisionSystemBase<CheckDynamicCollisionSystem> {
public:
	void update(Halley::Time time, MainFamily& e) {
		// TODO: make this more efficient
		if (e.collider->isStatic) {
			return;
		}

		auto myRect = e.position->position + e.collider->rect;
		for (auto& o : targetsFamily) {
			if (o.collider->isStatic) {
				return;
			}

			auto rect = o.position->position + o.collider->rect;
			if (myRect.overlaps(rect)) {
				sendMessage(e.entityId, CollisionMessage(o.entityId, o.collider->layer));
			}
		}
	}
};

REGISTER_SYSTEM(CheckDynamicCollisionSystem)

