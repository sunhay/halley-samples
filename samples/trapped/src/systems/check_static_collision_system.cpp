#include <systems/check_static_collision_system.h>
#include <limits>

using namespace Halley;

class CheckStaticCollisionSystem final : public CheckStaticCollisionSystemBase<CheckStaticCollisionSystem> {
public:
	void update(Time t, MainFamily& e)
	{
		EntityId myself = e.entityId;
		Vector2f startPos = e.position.position;
		Vector2f& endPos = e.velocity.targetPosition;
		Rect4f rect = e.position.position + e.collider.rect;

		// This is how much this entity wants to move
		const Vector2f desiredDelta = endPos - startPos;
		Vector2f delta;

		// Try moving it horizontally first...
		delta.x = moveHorizontal(myself, desiredDelta.x, rect);

		// Adjust the entity's collider based on where it'd end up, and try moving vertically from there
		rect += Vector2f(delta.x, 0);
		delta.y = moveVertical(myself, desiredDelta.y, rect);

		// This is where we end up
		endPos = startPos + delta;

		// If we hit an obstacle, update our velocity to reflect that
		if (t > 0.0001) {
			if (delta.x != desiredDelta.x) {
				e.velocity.velocity.x = delta.x / float(t);
			}
			if (delta.y != desiredDelta.y) {
				e.velocity.velocity.y = delta.y / float(t);
			}
		}
	}

private:
	float moveHorizontal(EntityId myself, float delta, const Rect4f& rect)
	{
		return delta == 0 ? 0 : move(myself, delta, 0, rect);
	}

	float moveVertical(EntityId myself, float delta, const Rect4f& rect)
	{
		return delta == 0 ? 0 : move(myself, delta, 1, rect);
	}

	float move(EntityId myself, float delta, int coord, Rect4f rect)
	{
		Range<float> myOrthogonal = rect.getRange(1 - coord);;
		Range<float> myNormal = rect.getRange(coord);

		float myPos = delta < 0 ? rect.getTopLeft()[coord] : rect.getBottomRight()[coord];
		float closest = delta < 0 ? std::numeric_limits<float>::lowest() : std::numeric_limits<float>::max();
		
		ObstaclesFamily* bestObstacle = nullptr;

		// TODO: only check surrounding area, instead of all obstacles
		for (auto& obstacle: obstaclesFamily) {
			if (obstacle.collider.isStatic) {
				auto colRect = obstacle.collider.rect + obstacle.position.position;

				// First check if there's an orthogonal overlap. If not, no matter how much I move along this axis, I can never collide with this obstacle.
				auto obsOrthogonal = colRect.getRange(1 - coord);
				if (myOrthogonal.overlaps(obsOrthogonal)) {
					// We'll also check for a normal overlap. If that's ALSO an overlap, then the two rectangles are overlapping (bad).
					auto obsNormal = colRect.getRange(coord);
					if (myNormal.overlaps(obsNormal)) {
						// We're inside the obstacle, oh shit.
						// TODO: handle this better
						onCollidedWith(myself, obstacle);
						return 0;
					}

					float obsPos = (delta > 0 ? colRect.getTopLeft() : colRect.getBottomRight())[coord];
					if ((delta < 0 && obsPos <= myPos && obsPos > closest) || (delta >= 0 && obsPos >= myPos && obsPos < closest)) {
						// Hit this obstacle, and this is closer to any previous found ones
						closest = obsPos;
						bestObstacle = &obstacle;
					}
				}
			}
		}
		float deltaToImpact = closest - myPos;

		if (abs(delta) < abs(deltaToImpact)) {
			// No obstacles hit
			return delta;
		} else {
			// Hit something
			if (bestObstacle) {
				onCollidedWith(myself, *bestObstacle);
			}
			return deltaToImpact;
		}
	}

	void onCollidedWith(EntityId dynamic, const ObstaclesFamily& obstacle)
	{
		sendMessage(dynamic, CollisionMessage(obstacle.entityId, obstacle.collider.layer, obstacle.collider.rect + obstacle.position.position));
	}

};

REGISTER_SYSTEM(CheckStaticCollisionSystem)

