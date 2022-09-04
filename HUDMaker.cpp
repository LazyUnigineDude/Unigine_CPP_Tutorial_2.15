#include "HUDMaker.h"

REGISTER_COMPONENT(HUDMaker)

void HUDMaker::Init(){
	GUI = Unigine::Gui::get();
	Canvas = Unigine::WidgetCanvas::create();
	Image = Unigine::WidgetSprite::create();

	int Width = Unigine::App::getWidth(), Height = Unigine::App::getHeight();

	// TEXT
	int x = Canvas->addText(1);
	Canvas->setTextColor(x, Unigine::Math::vec4(1,1,1,0.5));
	Canvas->setTextText(x, "SAMPLE_TEXT");
	Canvas->setTextSize(x, 30);
	Canvas->setTextPosition(x, Unigine::Math::vec2((Width / 2) - (Canvas->getTextWidth(x) / 2), (Height / 2) - (Canvas->getTextHeight(x) / 2)));

	// BOX
	int y = Canvas->addPolygon(0);
	Canvas->setPolygonColor(y, Unigine::Math::vec4(0, 0, 0, 0.5));
	Canvas->addPolygonPoint(y, Unigine::Math::vec3((Width / 2) - 200, (Height / 2) - 50, 0));
	Canvas->addPolygonPoint(y, Unigine::Math::vec3((Width / 2) + 200, (Height / 2) - 50, 0));
	Canvas->addPolygonPoint(y, Unigine::Math::vec3((Width / 2) + 200, (Height / 2) + 50, 0));
	Canvas->addPolygonPoint(y, Unigine::Math::vec3((Width / 2) - 200, (Height / 2) + 50, 0));

	// Crosshair
	int z = Image->addLayer();
	Unigine::ImagePtr _i = Unigine::Image::create(); _i->load(CrossHair.get());
	Image->setImage(_i);
	Image->setHeight(50);
	Image->setWidth(50);
	Image->setPosition((Width / 2) - (Image->getWidth()/2), Height / 2 - (Image->getHeight() / 2));
	

	//GUN
	CurrentAmount = Unigine::WidgetLabel::create();
	MaxAmount = Unigine::WidgetLabel::create();

	GUI->addChild(Image, GUI->ALIGN_FIXED | GUI->ALIGN_OVERLAP);
	//GUI->addChild(Canvas, GUI->ALIGN_EXPAND);
	GUI->addChild(CurrentAmount, GUI->ALIGN_FIXED | GUI->ALIGN_OVERLAP);
	GUI->addChild(MaxAmount, GUI->ALIGN_FIXED | GUI->ALIGN_OVERLAP);
}

void HUDMaker::Update()
{
	GUI = Unigine::Gui::get();
}

void HUDMaker::UpdateGun(int CAmount, int MAmount) {

	std::string Amount = std::to_string(CAmount);
	CurrentAmount->setText(Amount.c_str());
	CurrentAmount->setFontSize(48);
	CurrentAmount->setPosition(Width - 160, 20);

	Amount = std::to_string(MAmount);
	MaxAmount->setText(Amount.c_str());
	MaxAmount->setFontSize(48);
	MaxAmount->setPosition(Width - 80, 20);
}