#include "Camera.h"

Camera::Camera()
{
	vPos = glm::vec3(0.0f, 0.0f, 5.0f);
	vDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	vUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	UpdateDistance();

	vDegree = glm::vec3(0.0f, 0.0f, 0.0f);
}

GLvoid Camera::Move(GLchar cAxis, GLfloat fSign)
{
	switch (cAxis)
	{
	case 'x':
	{
		fDistance += fSign * 0.5f;

		break;
	}
	case 'y':
	{
		vPos.y += 0.5f;

		break;
	}
	case 'z':
	{
		vPos.z += 0.5f;

		break;
	}
	default:
		break;
	}
}

GLvoid Camera::Rotate(GLchar cAxis, GLfloat fSign)
{
	switch (cAxis)
	{
	case 'x':
	{
		vPos = glm::vec3(vPos.x, (GLfloat)sin(glm::radians(vDegree.x)) * fDistance, (GLfloat)cos(glm::radians(vDegree.x)) * fDistance);

		break;
	}
	case 'y':
	{
		vPos = glm::vec3((GLfloat)sin(glm::radians(vDegree.x)) * fDistance, vPos.y, (GLfloat)cos(glm::radians(vDegree.x)) * fDistance);

		break;
	}
	case 'z':
	{
		vPos = glm::vec3((GLfloat)sin(glm::radians(fSign * vDegree.z)) * fDistance, (GLfloat)cos(glm::radians(fSign * vDegree.z)) * fDistance, vPos.z);

		break;
	}
	default:
		break;
	}

	if (vDegree.x > 360.0f)
	{
		vDegree.x = 0.0f;
	}
	else
	{
		vDegree.x += fSign * 1.0f;
	}
}

GLvoid Camera::UpdateDistance()
{
	GLfloat distanceX = pow(vPos.x - vTarget.x, 2);
	GLfloat distanceY = pow(vPos.y - vTarget.y, 2);
	GLfloat distanceZ = pow(vPos.z - vTarget.z, 2);

	fDistance = sqrtf(distanceX + distanceY + distanceZ);
}

Camera::~Camera()
{

}