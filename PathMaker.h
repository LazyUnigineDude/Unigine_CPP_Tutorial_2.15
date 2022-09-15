#pragma once
#include <Unigine.h>

class PathMaker : public Unigine::ComponentBase{

public:
	COMPONENT_DEFINE(PathMaker, ComponentBase)
	PROP_PARAM(Node, ObjToMove)
	PROP_PARAM(Float, DurationTime)
	PROP_ARRAY(Node, PathPoints)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)

protected:
	void Init();
	void Update();

private:

	void RenderPath();
	Unigine::SplineGraphPtr Path;
	float Weight = 0;
	int num = 0;
};

