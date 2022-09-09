#include "ShooterAI.h"
REGISTER_COMPONENT(ShooterAI)

void ShooterAI::Update() {

	Unigine::Math::mat4 Frustum(Unigine::Math::perspective(40, 1.4f, 0.05, FieldDistance));
		Unigine::Math::quat Rotation(node->getWorldRotation() * Unigine::Math::quat(90, 0, 0));
		Unigine::Math::mat4 View(Rotation, node->getChild(0)->getWorldPosition());
	
		Unigine::Visualizer::renderFrustum(Frustum, View, Unigine::Math::vec4_black);
		Unigine::Visualizer::renderVector(node->getWorldPosition(), node->getWorldPosition() + node->getWorldDirection(Unigine::Math::AXIS_Y) * 2, Unigine::Math::vec4_black);

		BFrustum = Unigine::Math::BoundFrustum(Frustum, Unigine::Math::inverse(View));

		if (BFrustum.inside(MainCharacter->getWorldPosition())) {
			isInsideFrustum = true;
			float distance = Unigine::Math::distance(MainCharacter->getWorldPosition(), node->getWorldPosition());
			DistanceFactor = distance / FieldDistance;
		}
		else isInsideFrustum = false;

		AiState();
}

void ShooterAI::AiState() {

	switch (STATE)
	{
	case ShooterAI::IDLE:
		Unigine::Log::message("IDLE\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps(), 0.0f, 1.0f);
		if (isInsideFrustum) { ChangeState(CurrentState::ALERT); }
		break;
	case ShooterAI::ALERT:
		Unigine::Log::message("ALRT\n");
		Weight = Unigine::Math::clamp(Weight += Unigine::Game::getIFps() / DistanceFactor, 0.0f, 1.0f);
		if (Weight == 1.0f) { ChangeState(CurrentState::AGGRESSIVE); }
		if (!isInsideFrustum) { ChangeState(CurrentState::IDLE); }
		break;
	case ShooterAI::SEARCH:
		Unigine::Log::message("SRCH\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps() / 5, 0.0f, 1.0f);
		if (Weight == 0.0f) { ChangeState(CurrentState::IDLE); }
		if (isInsideFrustum) { ChangeState(CurrentState::AGGRESSIVE); Weight = 1; }
		break;
	case ShooterAI::AGGRESSIVE:
		Unigine::Log::message("AGRO\n");
		if (!isInsideFrustum) { ChangeState(CurrentState::SEARCH); }
		break;
	default:
		break;
	}
}