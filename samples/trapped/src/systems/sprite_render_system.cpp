#include "systems/sprite_render_system.h"

using namespace Halley;

class SpriteRenderSystem final : public SpriteRenderSystemBase<SpriteRenderSystem> {
public:
	void render(Painter& painter) const
	{
		Rect4f worldView = getWorldView(painter);

		spritePainter.start(mainFamily.count());
		for (auto& e : mainFamily) {
			auto& sprite = e.sprite.sprite;
			sprite.setPos(e.position.position);
			if (sprite.isInView(worldView)) {
				spritePainter.add(sprite, e.sprite.layer, int(sprite.getPosition().y - worldView.getY()));
			}
		}
		spritePainter.draw(painter);
	}

private:
	mutable SpritePainter spritePainter;

	Rect4f getWorldView(Painter& painter) const
	{
		Camera& cam = painter.getCurrentCamera();
		Rect4i viewPort = painter.getViewPort();

		Vector2f size = Vector2f(viewPort.getSize()) / cam.getZoom();
		assert(cam.getAngle().getRadians() == 0); // Camera rotation not accounted by following line
		return Rect4f(cam.getPosition() - size * 0.5f, size);
	}
};

REGISTER_SYSTEM(SpriteRenderSystem)
