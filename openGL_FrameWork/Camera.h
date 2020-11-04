#pragma once
#include "define.h"

class Camera
{
private:
	glm::vec3 vPos;					//ī�޶� ��ġ

	glm::vec3 vTarget;				//ī�޶� �ٶ󺸴� ��ǥ
	glm::vec3 vDirection;			//ī�޶��� ���⺤��(n����)

	glm::vec3 vUPVec;				//UP ����
	glm::vec3 vRight;				//u����

	glm::vec3 vUp;					//v����

public:
	Camera();
	~Camera();
public:
	GLvoid ViewTransform();			//��(ī�޶�)��ȯ
};