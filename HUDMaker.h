#pragma once
#include <Unigine.h>

class HUDMaker : public Unigine::ComponentBase
{
public:

	COMPONENT_DEFINE(HUDMaker, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(File, IMAGE)

protected:

	void Init();
	void Update();

	Unigine::GuiPtr GUI;
	Unigine::WidgetCanvasPtr Canvas;
	Unigine::WidgetSpritePtr Image;
};

