#pragma once
#include <Unigine.h>
#include <memory>
#include "PathMaker.h"
#include "HealthBar.h"

class ShooterAI : public Unigine::ComponentBase {

public:

	COMPONENT_DEFINE(ShooterAI, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(Node, MainCharacter)
		PROP_PARAM(Node, PathMakerNode)
	
	enum CurrentState{IDLE, ALERT, SEARCH, AGGRESSIVE, SHOOT};
	void ChangeState(CurrentState NEW_STATE) { if (STATE != NEW_STATE) { STATE = NEW_STATE; } }

protected:
	
	void Init();
	void Update();

private:
	void AiState();
	void RotateTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, float RoatateSpeed);
	void MoveTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, int Speed);
	CurrentState STATE  = CurrentState::IDLE;
	float Weight = 0, DistanceFactor = 1, CurrentTime = 0;
	int FieldDistance = 15, CurrentHealth;
	void Shoot() { Unigine::Log::message("BAM!\n"); }

	HealthBar* Health;
	PathMaker* Path;

	bool isInsideFrustum = false;
	Unigine::Math::BoundFrustum BFrustum;
	Unigine::Vector<Unigine::NodePtr> ObjCaptured;
};