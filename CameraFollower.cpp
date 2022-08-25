#include "CameraFollower.h"

REGISTER_COMPONENT(CameraFollower)


void CameraFollower::Init() { MainCamera = Unigine::Game::getPlayer(); }

void CameraFollower::Regular() {

	MousePosition = Unigine::Input::getMouseCoordDelta();

	Angle += MousePosition.x * Unigine::Game::getIFps() * Rotation_Speed_Horizontal.get();

	Height = Unigine::Math::clamp(
		Height += MousePosition.y * Unigine::Game::getIFps() * Rotation_Speed_Vertical.get(),
		Min_Max_Height.get().x,
		Min_Max_Height.get().y
	);

	NPoint.x = Radius.get() * Unigine::Math::cos(Angle);
	NPoint.y = Radius.get() * Unigine::Math::sin(Angle);
	NPoint.z = 1.5f;

	NPoint += Object_To_Rotate.get()->getWorldPosition();

	Object_To_Follow.get().get()->setWorldPosition(NPoint);

	CPoint.x = (Radius.get() + 2) * Unigine::Math::cos(Angle - 20);
	CPoint.y = (Radius.get() + 2) * Unigine::Math::sin(Angle - 20);
	CPoint.z = Height;

	CPoint += Object_To_Rotate.get()->getWorldPosition();

	MainCamera->setWorldPosition(CPoint);
	MainCamera->worldLookAt(Object_To_Follow.get()->getWorldPosition());
}

void CameraFollower::Aiming() {

	MousePosition = Unigine::Input::getMouseCoordDelta();

	Angle += MousePosition.x * Unigine::Game::getIFps() * Rotation_Speed_Horizontal.get();

	Height = Unigine::Math::clamp(
		Height += MousePosition.y * Unigine::Game::getIFps() * Rotation_Speed_Vertical.get(),
		-0.5f,
		 2.5f
	);

	NPoint.x = 1 * Unigine::Math::cos(Angle);
	NPoint.y = 1 * Unigine::Math::sin(Angle);
	NPoint.z = 1.0f;

	NPoint += Object_To_Rotate.get()->getWorldPosition();

	Object_To_Follow.get().get()->setWorldPosition(NPoint);

	CPoint.x = 2 * Unigine::Math::cos(Angle - 20);
	CPoint.y = 2 * Unigine::Math::sin(Angle - 20);
	CPoint.z = Height;

	CPoint += Object_To_Rotate.get()->getWorldPosition();

	MainCamera->setWorldPosition(CPoint);
	MainCamera->worldLookAt(Object_To_Follow.get()->getWorldPosition());
}

void CameraFollower::Update() {

	(isAiming) ? Aiming() : Regular();

}