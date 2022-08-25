#pragma once
#include <Unigine.h>

class ShooterAnim : public Unigine::ComponentBase
{

public:
	COMPONENT_DEFINE(ShooterAnim, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_ARRAY(File, ANIM_NORMAL)
		PROP_ARRAY(File, ANIM_EQUIP)
		PROP_ARRAY(File, ANIM_AIM)
		PROP_PARAM(File, GunShot_VFX)
		//PROP_PARAM(Toggle, isEquipped)
		void ChangeStateToEquipped();

protected:
	void Init();
	void Update();

private:

	Unigine::ObjectMeshSkinnedPtr MainCharacter;
	float Weight = 0, Weight_ = 0, x = 2, y = 5;
	bool isWeightChanged = false;

	enum ANIMSTATES { IDLE, WALK, RUN, REVERSE_WALK, COUNT };
	enum SHOOTER_STATE { NORMAL, EQUIPPED, AIMED, _COUNT };
	

	void ResetWeight();
	void ChangeState(int SHOOTERSTATE);
	void ShooterState();
	
	SHOOTER_STATE State = SHOOTER_STATE::NORMAL;
	ANIMSTATES MainState = ANIMSTATES::IDLE, PrevState = ANIMSTATES::IDLE;
	
	Unigine::ObjectPtr Gun;
	Unigine::NodeReferencePtr BulletPrefab;
	Unigine::Vector<Unigine::NodePtr> ObjectsCaptured;
};

