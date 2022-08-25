#pragma once
#include <Unigine.h>

class CameraFollower : public Unigine::ComponentBase
{

public:

	COMPONENT_DEFINE(CameraFollower, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)

		PROP_PARAM(Node, Object_To_Follow)
		PROP_PARAM(Node, Object_To_Rotate)
		PROP_PARAM(Float, Radius, 2)
		PROP_PARAM(Float, Rotation_Speed_Horizontal, 0.5f)
		PROP_PARAM(Float, Rotation_Speed_Vertical, 0.5f)
		PROP_PARAM(Vec2, Min_Max_Height, Unigine::Math::vec2(-0.5f, 4))

		bool isAiming = false;

protected:
	void Init();
	void Update();

private:

	Unigine::PlayerPtr MainCamera;
	Unigine::Math::ivec2 MousePosition;
	Unigine::Math::Vec3 NPoint;
	Unigine::Math::Vec3 CPoint;

	float Angle;
	float Height;

	void Regular();
	void Aiming();
};

