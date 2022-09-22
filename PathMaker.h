#pragma once
#include <Unigine.h>
#include <vector>

class PathMaker : public Unigine::ComponentBase{

public:
	COMPONENT_DEFINE(PathMaker, ComponentBase)
		PROP_PARAM(Node, ObjToMove)
		PROP_PARAM(Float, DurationTime)
		PROP_ARRAY(Node, PathPoints)

		void InitPath();
		void ObjectToMove(Unigine::NodePtr Object, int Pos, float Time);
		void RenderPath();
		void MoveAlongPath();
		float Weight = 0;
		int num = 0;

private:

	Unigine::SplineGraphPtr Path;
};