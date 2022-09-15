#include "PathMaker.h"
REGISTER_COMPONENT(PathMaker)

void PathMaker::Init() {

	Path = Unigine::SplineGraph::create();

	for (int i = 0; i < PathPoints.size();  i++) { Path->addPoint(PathPoints[i]->getWorldPosition()); }

	Path->addSegment(0, PathPoints[0]->getWorldDirection(Unigine::Math::AXIS_Y), PathPoints[0]->getWorldDirection(Unigine::Math::AXIS_Z),
					 1, PathPoints[1]->getWorldDirection(Unigine::Math::AXIS_NY), PathPoints[1]->getWorldDirection(Unigine::Math::AXIS_Z));
	Path->addSegment(1, PathPoints[1]->getWorldDirection(Unigine::Math::AXIS_Y), PathPoints[1]->getWorldDirection(Unigine::Math::AXIS_Z),
					 2, PathPoints[2]->getWorldDirection(Unigine::Math::AXIS_NY), PathPoints[2]->getWorldDirection(Unigine::Math::AXIS_Z));
	Path->addSegment(2, PathPoints[2]->getWorldDirection(Unigine::Math::AXIS_Y), PathPoints[2]->getWorldDirection(Unigine::Math::AXIS_Z),
					 3, PathPoints[3]->getWorldDirection(Unigine::Math::AXIS_NY), PathPoints[3]->getWorldDirection(Unigine::Math::AXIS_Z));
	Path->addSegment(3, PathPoints[3]->getWorldDirection(Unigine::Math::AXIS_Y), PathPoints[3]->getWorldDirection(Unigine::Math::AXIS_Z),
					 0, PathPoints[0]->getWorldDirection(Unigine::Math::AXIS_NY), PathPoints[0]->getWorldDirection(Unigine::Math::AXIS_Z));

}

void PathMaker::Update() {

	Weight = Unigine::Math::clamp(Weight += (Unigine::Game::getIFps() / DurationTime), 0.0f, 1.0f);
	if (Weight == 1.0f) { Weight = 0; num++; }
	num %= Path->getNumPoints();

	Unigine::Math::vec3 
		Point = Path->calcSegmentPoint(num, Weight),
		Dir	  = Path->calcSegmentTangent(num, Weight),
		Up    = Path->calcSegmentUpVector(num, Weight);

	ObjToMove->setWorldPosition(Point);
	ObjToMove->setWorldDirection(Dir, Up, Unigine::Math::AXIS_Y);

	RenderPath();
}

void PathMaker::RenderPath() { 

	const int segments = 50;

	for (int i = 0; i < Path->getNumPoints(); i++)
	{
		Unigine::Math::vec3 Point = Path->getPoint(i);
		Unigine::Visualizer::renderPoint3D(Point, 0.1f, Unigine::Math::vec4_black);

		Unigine::Math::vec3
			SPoint = Path->getSegmentStartPoint(i),
			STang = Path->getSegmentStartTangent(i),
			EPoint = Path->getSegmentEndPoint(i),
			ETang = Path->getSegmentEndTangent(i);

		Unigine::Visualizer::renderVector(SPoint, SPoint + STang, Unigine::Math::vec4_green);
		Unigine::Visualizer::renderVector(EPoint, EPoint + ETang, Unigine::Math::vec4_red);

		for (int j = 0; j < segments; j++)
		{
			Unigine::Math::vec3
				p0 = Path->calcSegmentPoint(i, j / segments),
				p1 = Path->calcSegmentPoint(i, (j +1) / segments);

			Unigine::Visualizer::renderLine3D(p0, p1, Unigine::Math::vec4_white);
		}

	}
}