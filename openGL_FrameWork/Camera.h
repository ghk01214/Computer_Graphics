#pragma once
#include "define.h"

class Camera
{
private:
	glm::vec3 vPos;					//카메라 위치

	glm::vec3 vTarget;				//카메라가 바라보는 좌표
	glm::vec3 vDirection;			//카메라가 바라보는 방향

	glm::vec3 vUPVec;				//UP 벡터
	glm::vec3 vRight;				//u벡터

	glm::vec3 vUp;					//v벡터

	GLfloat fDistance;
	GLfloat fDegree;

public:
	Camera();
	~Camera();
public:
	//Input 함수
	GLvoid InputRoateAngle(GLfloat fDegree) { this->fDegree = fDegree; }
public:
	//Return 함수
	glm::vec3 ReturnCameraPos() { return vPos; }
	glm::vec3 ReturnCameraDirection() { return vDirection; }
	glm::vec3 ReturnCameraUp() { return vUp; }
public:
	GLvoid Move(GLchar);
	GLvoid Rotate(GLchar cAxis, GLfloat fSign);
	GLvoid UpdateDistance();
};