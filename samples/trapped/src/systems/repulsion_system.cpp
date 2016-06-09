#include <systems/repulsion_system.h>

using namespace Halley;

class RepulsionSystem final : public RepulsionSystemBase<RepulsionSystem> {
public:
	void update(Halley::Time time, MainFamily& e) {
	}
	
	void onMessageReceived(const CollisionMessage& msg, MainFamily& entity) {
		// Only bounce against other things with repulsion
		if (!getWorld().getEntity(msg.other).hasComponent<RepulseFieldComponent>()) {
			return;
		}

		auto myRect = entity.collider.rect + entity.position.position;
		auto theirRect = msg.otherRect;

		// Find the bounce-out direction
		Vector2f c0 = myRect.getCenter();
		Vector2f c1 = theirRect.getCenter();
		Vector2f dir = (c0 - c1).unit();

		// If they're too close, it might fail. Disambiguate
		if (dir.squaredLength() < 0.1f) {
			dir.x = dir.y = entity.entityId < msg.other ? -1.0f : 1.0f;
			dir.normalize();
		}
		
		// Get the overlap amount
		Vector2f overlap;
		overlap.x = myRect.getHorizontal().getOverlap(theirRect.getHorizontal()).getLength();
		overlap.y = myRect.getVertical().getOverlap(theirRect.getVertical()).getLength();
		Vector2f axes(abs(dir.x), abs(dir.y));

		// Compute speed and bounce
		float overlapDist = axes.dot(overlap) + 2;
		float speed = overlapDist * entity.repulseField.multiplier;
		entity.velocity.velocity += dir * speed;
	}
};

REGISTER_SYSTEM(RepulsionSystem)

