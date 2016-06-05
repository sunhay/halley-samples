#include <systems/player_input_system.h>

class PlayerInputSystem final : public PlayerInputSystemBase<PlayerInputSystem> {
public:
	void update(Halley::Time, MainFamily& entity)
	{
		auto& input = entity.playerInput->input;
		auto moveDir = Halley::Vector2f(input->getAxis(0), input->getAxis(1));
		auto shootDir = Halley::Vector2f(input->getAxis(2), input->getAxis(3));

		bool shooting = shootDir.length() > 0.1f;
		Halley::Vector2f faceDir = shooting ? shootDir : moveDir;

		entity.mob->moveDir = moveDir;
		
		if (faceDir.squaredLength() > 0.1f) {
			entity.mob->faceDir = faceDir.unit();
		}
	}
};

REGISTER_SYSTEM(PlayerInputSystem)
