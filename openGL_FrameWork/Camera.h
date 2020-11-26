#pragma once
#include "define.h"

class Camera
{
private:
	glm::vec3 vPos;					//ī�޶� ��ġ

	glm::vec3 vTarget;				//ī�޶� �ٶ󺸴� ��ǥ
	glm::vec3 vDirection;			//ī�޶� �ٶ󺸴� ����

	glm::vec3 vUPVec;				//UP ����
	glm::vec3 vRight;				//u����

	glm::vec3 vUp;					//v����

	GLfloat fDistance;				//ī�޶�� �ٶ󺸴� ��ǥ ������ �Ÿ�
	GLfloat fSpeed;
	glm::vec3 vDegree;				//ȸ�� ����

	GLfloat fDeltaTime;
	GLfloat fCurrentFrame;
	GLfloat fLastFrame;

public:
	Camera();
	~Camera();
public:
	//Input �Լ�

public:
	//Return �Լ�
	glm::vec3 ReturnCameraPos() { return vPos; }
	glm::vec3 ReturnCameraDirection() { return vDirection; }
	glm::vec3 ReturnCameraUp() { return vUp; }
public:
	GLvoid Move(GLchar cAxis, GLfloat fSign);
	GLvoid Rotate(GLchar cAxis, GLfloat fSign);

	GLvoid UpdateDistance();
	GLfloat LinearFunction(GLfloat fPos, GLfloat fSign);
};