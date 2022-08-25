#pragma once
#include <Unigine.h>


class Shooter_ : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Shooter_,ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)

protected:
	void Init();
	void Update();	

private:

	Unigine::Node Equip;

};

