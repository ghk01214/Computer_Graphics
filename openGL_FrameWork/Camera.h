#pragma once

class Camera
{
private:
	glm::vec3 vPos;				//ī�޶� ��ġ
	glm::vec3 vTarget;			//ī�޶� ���� ��ġ
	glm::vec3 vUp;				//v(Up) ����

	glm::vec3 vDirection;
private:
	glm::vec3 vDegree;			//ī�޶� ȸ�� ����
	glm::vec3 deltaPos;
	glm::vec3 deltaTarget;

	glm::vec3 vPosPin;
	glm::vec3 vTargetPin;
public:
	Camera();
	~Camera();
public:
	glm::vec3 ReturnPos() { return vPos; }
	glm::vec3 ReturnTarget() { return vTarget; }
	glm::vec3 ReturnUp() { return vUp; }
public:
	GLvoid InputPos(glm::vec3 pos) { vPos = pos; }
	GLvoid InputTarget(glm::vec3 target) { vTarget = target; }
	GLvoid InputDirection(glm::vec3 direction) { vDirection = direction; }
	GLvoid InputUp(glm::vec3 up) { vUp = up; }
public:
	GLvoid Move(GLint iDirection, GLfloat fSpeed);
	GLvoid Rotate(GLfloat fSign);
public:
	GLfloat UpdateDistance();
	GLfloat LinearFunction(GLfloat attribX);
	GLfloat NormalFunction(GLfloat attribX);
public:
	enum Direction
	{
		Forward, Backward, Left, Right
	};
};