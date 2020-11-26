#include "Camera.h"

Camera::Camera()
{
	vPos = glm::vec3(0.0f, 0.0f, -5.0f);
	vTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	vDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	vUp = glm::vec3(0.0f, 1.0f, 0.0f);

	fDeltaTime = 0.0f;
	fLastFrame = 0.0f;

	UpdateDistance();
	fSpeed = 0.1f;

	vDegree = glm::vec3(180.0f, 180.0f, 0.0f);
}

GLvoid Camera::Move(GLchar cAxis, GLfloat fSign)
{
	switch (cAxis)
	{
	case 'x':
	{
		vPos.x += fSign * fSpeed;
		vDirection.x += fSign * fSpeed;

		vPos.z = LinearFunction(vPos.x, -1);
		vDirection.z = LinearFunction(vDirection.x, -1);

		break;
	}
	case 'z':
	{
		vPos.z += fSign * fSpeed;
		vDirection.z += fSign * fSpeed;

		//LinearFunction(vPos.x, 1);
		//LinearFunction(vDirection.x, 1);

		break;
	}
	default:
		break;
	}

	UpdateDistance();
}

GLvoid Camera::Rotate(GLchar cAxis, GLfloat fSign)
{
	switch (cAxis)
	{
	case 'x':
	{
		vPos.y = (GLfloat)sin(glm::radians(vDegree.y)) * fDistance;
		vPos.z = (GLfloat)cos(glm::radians(vDegree.y)) * fDistance;

		if (vDegree.y < 269.0f && vDegree.y > 89.0f)
		{
			vDegree.y += fSign * 1.0f;
		}

		break;
	}
	case 'y':
	{
		vPos.x = (GLfloat)sin(glm::radians(vDegree.x)) * fDistance;
		vPos.z = (GLfloat)cos(glm::radians(vDegree.x)) * fDistance;

		vDegree.x += fSign * 1.0f;

		break;
	}
	default:
		break;
	}
}

GLvoid Camera::UpdateDistance()
{
	GLfloat distanceX = pow(vPos.x - vDirection.x, 2);
	GLfloat distanceY = pow(vPos.y - vDirection.y, 2);
	GLfloat distanceZ = pow(vPos.z - vDirection.z, 2);

	fDistance = sqrtf(distanceX + distanceY + distanceZ);
}

GLfloat Camera::LinearFunction(GLfloat fPos, GLfloat fSign)
{
	GLfloat fGrade = (vDirection.z - vPos.z) / (vDirection.x - vPos.x);

	return fGrade * (fSign * fPos - vPos.x) + vPos.z;
}

Camera::~Camera()
{

}