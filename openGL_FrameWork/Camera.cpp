#include "Camera.h"

Camera::Camera()
{
	vPos = glm::vec3(0.0f, 0.0f, 5.0f);
	vDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	vUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	UpdateDistance();

	fDegree = 0.0f;
}

GLvoid Camera::Move(GLchar cAxis)
{
	switch (cAxis)
	{
	case 'x':
	{
		vPos.x += 0.5f;

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
		if (fDegree < 90.0f)
			vPos = glm::vec3(vPos.x, (GLfloat)sin(glm::radians(fSign * fDegree)) * fDistance, (GLfloat)cos(glm::radians(fSign * fDegree)) * fDistance);
		std::cout << fDegree << std::endl;
		break;
	}
	case 'y':
	{
		vPos = glm::vec3((GLfloat)sin(glm::radians(fSign * fDegree)) * fDistance, vPos.y, (GLfloat)cos(glm::radians(fSign * fDegree)) * fDistance);

		break;
	}
	case 'z':
	{
		vPos = glm::vec3((GLfloat)sin(glm::radians(fSign * fDegree)) * fDistance, (GLfloat)cos(glm::radians(fSign * fDegree)) * fDistance, vPos.z);

		break;
	}
	default:
		break;
	}

	if (fDegree > 360.0f)
	{
		fDegree = 0.0f;
	}
	else
	{
		fDegree += fSign * 1.0f;
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