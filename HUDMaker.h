#pragma once
#include <Unigine.h>
#include <string>

class HUDMaker : public Unigine::ComponentBase
{
public: 
	
	COMPONENT_DEFINE(HUDMaker, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(File, CrossHair)

		void UpdateGun(int CurrentAmount,int MaxAmount); 

protected:

	void Init();
	void Update();

private:

	int Width = Unigine::App::getWidth(), Height = Unigine::App::getHeight();
	Unigine::GuiPtr GUI;
	Unigine::WidgetCanvasPtr Canvas;
	Unigine::WidgetSpritePtr Image;
	Unigine::WidgetLabelPtr CurrentAmount, MaxAmount;
};

