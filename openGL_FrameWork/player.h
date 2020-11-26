#pragma once
#include "Shader3D.h"

class Player
{
private:
	BaseShader* bPart;
	GLuint uiVAO;
	GLuint uiVBO[Num::VBO];
	GLuint uiEBO;
private:
	Camera cView;

	std::vector<GLint> vType;
public:
	Player(Camera cView);
	~Player();
public:
	GLvoid InputCameraAttribute(Camera cView) { this->cView = cView; }
public:
	GLvoid ModelHead();
	GLvoid ModelBody();
	GLvoid ModelArms();
	GLvoid ModelLegs();
public:
	GLvoid Render();
};