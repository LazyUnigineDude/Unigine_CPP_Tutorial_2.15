#pragma once
#include <Unigine.h>
#include "Bullet.h"


class GunHandler : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(GunHandler, ComponentBase)
		COMPONENT_UPDATE_PHYSICS(Update)
		void GetGun(Unigine::ObjectPtr Gun);
	

protected:
	void Update();

private:

	void Shoot(Unigine::Math::vec3& Lookat);
	Unigine::NodeReferencePtr BulletPrefab;
	Unigine::ObjectPtr Gun = nullptr;
	float RateofFireTime = 0, RoF = 1;
	bool isHolding = false;
};

