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

	GLfloat fDistance;
	GLfloat fDegree;

public:
	Camera();
	~Camera();
public:
	//Input �Լ�
	GLvoid InputRoateAngle(GLfloat fDegree) { this->fDegree = fDegree; }
public:
	//Return �Լ�
	glm::vec3 ReturnCameraPos() { return vPos; }
	glm::vec3 ReturnCameraDirection() { return vDirection; }
	glm::vec3 ReturnCameraUp() { return vUp; }
public:
	GLvoid Move(GLchar);
	GLvoid Rotate(GLchar cAxis, GLfloat fSign);
	GLvoid UpdateDistance();
};