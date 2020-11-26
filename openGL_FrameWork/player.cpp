#include "player.h"

Player::Player(Camera cView)
{
	InputCameraAttribute(cView);
}

Player::~Player()
{
}

GLvoid Player::ModelHead()
{
	Pos pCenter = { 0.0f, 0.0f, 0.0f };

	bPart = new Shader3D(482);

	bPart->InputTranslatePos(1.5f, 'y', 1.0f);
	bPart->TranslateWorld();

	bPart->InputScaleSize(0.07f, 'a', 1.0f);
	bPart->ScaleWorld();

	bPart->MoveCamera(cView);
	bPart->CreateObject(Manage::Sphere, pCenter);
}

GLvoid Player::ModelBody()
{
	Pos pCenter = { 0.0f, 0.0f, 0.0f };

	bPart = new Shader3D(8);

	bPart->InputTranslatePos(0.5f, 'y', 1.0f);
	//bPart->TranslateWorld();

	bPart->InputScaleSize(1.5f, 'y', 1.0f);
	bPart->ScaleWorld();

	bPart->InputScaleSize(1.5f, 'x', 1.0f);
	bPart->ScaleWorld();

	bPart->InputScaleSize(1.5f, 'x', -1.0f);
	//bPart->ScaleWorld();

	bPart->MoveCamera(cView);
	bPart->CreateObject(Manage::Cube, pCenter);
}

GLvoid Player::ModelArms()
{
	return GLvoid();
}

GLvoid Player::ModelLegs()
{
	Pos pCenter = { 0.0f, 0.0f, 0.0f };

	bPart = new Shader3D(8);

	bPart->InputTranslatePos(0.3f, 'y', -1.0f);
	bPart->TranslateWorld();

	bPart->InputScaleSize(2.0f, 'y', 1.0f);
	bPart->ScaleWorld();

	bPart->MoveCamera(cView);
	bPart->CreateObject(Manage::Cube, pCenter);
}

GLvoid Player::Render()
{
	ModelHead();
	ModelBody();
}