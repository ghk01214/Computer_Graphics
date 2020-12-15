#pragma once
#include "Shader3D.h"

class Player
{
private:
	BaseShader* bShader;
	std::vector<BaseShader*> vPart;
private:
	glm::vec3 vPos;
	glm::vec3 vTarget;
	glm::vec3 vDirection;

	glm::vec3 vPosPin;
	glm::vec3 vTargetPin;
	glm::vec3 vPosB;
	glm::vec3 vTargetB;

	glm::vec3 deltaPos;
	glm::vec3 deltaTarget;

	GLfloat fDegree;
public:
	Player();
	Player(Camera cView);
	~Player();
public:
	glm::vec3 ReturnPos() { return vPos; }
	glm::vec3 ReturnTarget() { return vTarget; }
	glm::vec3 ReturnDirection() { return vDirection; }
public:
	GLvoid ModelPlayer(Camera cView);
	GLvoid ModelHead(Camera cView);
	GLvoid ModelBody(Camera cView);
	GLvoid ModelArms(Camera cView);
	GLvoid ModelLegs(Camera cView);
public:
	GLvoid Move(GLint iDirection, GLfloat fSpeed);
	GLvoid MoveObject(GLfloat fSpeed, GLfloat fSign, GLbool x);
	GLvoid Rotate(GLfloat fSign);

	GLvoid View(Camera cView);
public:
	GLfloat UpdateDistance();
	GLfloat LinearFunction(GLfloat attribX);
	GLfloat NormalFunction(GLfloat attribX);
public:
	GLvoid Render();
public:
	enum Direction
	{
		Forward, Backward, Left, Right
	};
};