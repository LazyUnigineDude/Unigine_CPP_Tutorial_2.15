#include "ShooterAI.h"
REGISTER_COMPONENT(ShooterAI)

void ShooterAI::Init() {
	
	Path = getComponent<PathMaker>(PathMakerNode);
}

void ShooterAI::Update() {

	// Calculate the Area, Position and Rotation
	Unigine::Math::mat4 Frustum(Unigine::Math::perspective(40, 1.4f, 0.05, FieldDistance));
		Unigine::Math::quat Rotation(node->getWorldRotation() * Unigine::Math::quat(90, 0, 0));
		Unigine::Math::mat4 View(Rotation, node->getChild(0)->getWorldPosition());
	
		// Render
		Unigine::Visualizer::renderFrustum(Frustum, View, Unigine::Math::vec4_black);
		Unigine::Visualizer::renderVector(node->getWorldPosition(), node->getWorldPosition() + node->getWorldDirection(Unigine::Math::AXIS_Y) * 2, Unigine::Math::vec4_black);

		// Logic
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
		//Unigine::Log::message("IDLE\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps(), 0.0f, 1.0f);
		if (isInsideFrustum) { ChangeState(CurrentState::ALERT); }
			if (Unigine::Math::distance(node->getWorldPosition(),Path->GetCurrentPathPosition()) > 0.1f) {
				RotateTowards(Path->GetCurrentPathPosition(), node, 0.05f);
				MoveTowards(Path->GetCurrentPathPosition(), node);
			}
			else {
				Path->MoveAlongPath();
				Path->MoveObject(node);
			}
		break;
	case ShooterAI::ALERT:
		//Unigine::Log::message("ALRT\n");
		Weight = Unigine::Math::clamp(Weight += Unigine::Game::getIFps() / DistanceFactor, 0.0f, 1.0f);
		if (Weight == 1.0f) { ChangeState(CurrentState::AGGRESSIVE); }
		if (!isInsideFrustum) { ChangeState(CurrentState::IDLE); }
			RotateTowards(MainCharacter->getWorldPosition(), node, 0.005f);
		break;
	case ShooterAI::SEARCH:
		//Unigine::Log::message("SRCH\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps() / 5, 0.0f, 1.0f);
		if (Weight == 0.0f) { ChangeState(CurrentState::IDLE); }
		if (isInsideFrustum) { ChangeState(CurrentState::AGGRESSIVE); Weight = 1; }
			RotateTowards(MainCharacter->getWorldPosition(), node, 0.05f);
		break;
	case ShooterAI::AGGRESSIVE:
		//Unigine::Log::message("AGRO\n");
		if (!isInsideFrustum) { ChangeState(CurrentState::SEARCH); }
			RotateTowards(MainCharacter->getWorldPosition(), node, 0.05f);
			MoveTowards(MainCharacter->getWorldPosition(), node);
		break;
	default: break;
	}
}

void ShooterAI::RotateTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, float RoatateSpeed) {

	Unigine::Math::Vec3 Vec1 = Obj2Move->getWorldDirection(Unigine::Math::AXIS_Y),
						Vec2 = (RotateTowards - Obj2Move->getWorldPosition()).normalize();

	float Angle = Unigine::Math::getAngle(Vec1, Vec2, Unigine::Math::vec3_up);
	Obj2Move->rotate(-Obj2Move->getWorldRotation().x, -Obj2Move->getWorldRotation().y, Angle * RoatateSpeed);
}

void ShooterAI::MoveTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move) {

	Unigine::Math::Vec3 Pos = Unigine::Math::lerp(
		Obj2Move->getWorldPosition(),
		RotateTowards,
		Unigine::Game::getIFps() /
		Unigine::Math::distance(Obj2Move->getWorldPosition(), RotateTowards));
	Obj2Move->setWorldPosition(Pos);
}
