#pragma once
#include "define.h"

class Camera
{
private:
	glm::vec3 vPos;					//카메라 위치

	glm::vec3 vTarget;				//카메라가 바라보는 좌표
	glm::vec3 vDirection;			//카메라의 방향벡터(n벡터)

	glm::vec3 vUPVec;				//UP 벡터
	glm::vec3 vRight;				//u벡터

	glm::vec3 vUp;					//v벡터

public:
	Camera();
	~Camera();
public:
	GLvoid ViewTransform();			//뷰(카메라)변환
};