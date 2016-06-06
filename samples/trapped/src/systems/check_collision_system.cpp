#include <systems/check_collision_system.h>

using namespace Halley;

class CheckCollisionSystem final : public CheckCollisionSystemBase<CheckCollisionSystem> {
public:
	void update(Time, MainFamily& e)
	{
		EntityId myself = e.entityId;
		Vector2f startPos = e.position->position;
		Vector2f& endPos = e.velocity->targetPosition;

		Vector2f sz = e.collider->size;
		Rect4f rect = Rect4f(e.position->position - sz / 2, sz.x, sz.y);

		Vector2f delta = endPos - startPos;
		delta.x = moveHorizontal(myself, delta.x, rect);
		rect.setX(rect.getX() + delta.x);
		delta.y = moveVertical(myself, delta.y, rect);

		endPos = startPos + Vector2f(delta);
	}

private:
	float moveHorizontal(EntityId myself, float delta, const Rect4f& rect)
	{
		return move(myself, delta, 0, rect);
	}

	float moveVertical(EntityId myself, float delta, const Rect4f& rect)
	{
		return move(myself, delta, 1, rect);
	}

	float move(EntityId myself, float delta, int coord, Rect4f rect)
	{
		if (delta == 0) return 0;

		Range<float> myOrthogonal(rect.getP1()[1 - coord], rect.getP2()[1 - coord]);
		float objPos = delta < 0 ? rect.getP1()[coord] : rect.getP2()[coord];

		float closest = delta < 0 ? -999999.0f : 999999.0f;
		
		EntityId obstacleEntity = -1;
		int obstacleLayer = -1;

		for (auto& obstacle: obstaclesFamily) {
			if (obstacle.collider->isStatic) {
				const auto& col = *obstacle.collider;
				Vector2f colLen = 0.5f * col.size;
				Vector2f pos = obstacle.position->position + col.offset;
				Vector2f p0 = pos - colLen;
				Vector2f p1 = pos + colLen;

				Range<float> obsOrthogonal(p0[1 - coord], p1[1 - coord]);
				if (myOrthogonal.overlaps(obsOrthogonal)) {
					if (delta < 0) {
						// Going left/up
						float obsPos = p1[coord];
						if (obsPos <= objPos && obsPos > closest) {
							closest = obsPos;
							obstacleEntity = obstacle.entityId;
							obstacleLayer = obstacle.collider->layer;
						}
					} else {
						// Going right/down
						float obsPos = p0[coord];
						if (obsPos >= objPos && obsPos < closest) {
							closest = obsPos;
							obstacleEntity = obstacle.entityId;
							obstacleLayer = obstacle.collider->layer;
						}
					}
				}
			}
		}
		float impactDelta = closest - objPos;

		if (abs(delta) < abs(impactDelta)) {
			return delta;
		} else {
			onCollidedWith(myself, obstacleEntity, obstacleLayer);
			return impactDelta;
		}
	}

	void onCollidedWith(EntityId dynamic, EntityId obstacle, int obstacleLayer)
	{
		sendMessage(dynamic, CollisionMessage(obstacle, obstacleLayer));
	}

};

REGISTER_SYSTEM(CheckCollisionSystem)

