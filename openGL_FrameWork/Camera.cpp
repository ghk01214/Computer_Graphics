#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	vPos = glm::vec3(0.0f, 4.0f, -5.0f);
	vTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	vUp = glm::vec3(0.0f, 1.0f, 0.0f);

	vDirection = vTarget - vPos;

	deltaPos = glm::vec3(0.0f, 0.0f, 0.0f);
	deltaTarget = glm::vec3(0.0f, 0.0f, 0.0f);

	vDegree = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
}

GLvoid Camera::Move(GLint iDirection, GLfloat fSpeed)
{
	glm::vec3 temp[2];

	temp[0] = vPos;
	temp[1] = vTarget;

	vDirection = vTarget - vPos;

	switch (iDirection)
	{
	case Forward:
	{
		if (vDirection.x < 0.0f)
		{
			vPos.x -= fSpeed;
			vTarget.x -= fSpeed;
		}
		else if (vDirection.x > 0.0f)
		{
			vPos.x += fSpeed;
			vTarget.x += fSpeed;
		}

		if (vDirection.x == 0.0f)
		{
			if (vDirection.z > 0.0f)
			{
				vPos.z += fSpeed;
				vTarget.z += fSpeed;
			}
			else
			{
				vPos.z -= fSpeed;
				vTarget.z -= fSpeed;
			}
		}
		else
		{
			vPos.z = LinearFunction(vPos.x);
			vTarget.z = LinearFunction(vTarget.x);
		}

		break;
	}
	case Backward:
	{
		if (vDirection.x < 0.0f)
		{
			vPos.x += fSpeed;
			vTarget.x += fSpeed;
		}
		else if (vDirection.x > 0.0f)
		{
			vPos.x -= fSpeed;
			vTarget.x -= fSpeed;
		}

		if (vDirection.x == 0.0f)
		{
			if (vDirection.z > 0.0f)
			{
				vPos.z -= fSpeed;
				vTarget.z -= fSpeed;
			}
			else
			{
				vPos.z += fSpeed;
				vTarget.z += fSpeed;
			}
		}
		else
		{
			vPos.z = LinearFunction(vPos.x);
			vTarget.z = LinearFunction(vTarget.x);
		}

		break;
	}
	case Left:
	{
		if (vDirection.x < 0.0f)
		{
			vPos.x -= fSpeed;
			vTarget.x -= fSpeed;
		}
		else if (vDirection.x > 0.0f)
		{
			vPos.x += fSpeed;
			vTarget.x += fSpeed;
		}

		if (vDirection.x == 0.0f)
		{
			if (vDirection.z > 0.0f)
			{
				vPos.x += fSpeed;
				vTarget.x += fSpeed;
			}
			else
			{
				vPos.x -= fSpeed;
				vTarget.x -= fSpeed;
			}
		}
		else
		{
			vPos.z = NormalFunction(vPos.x);
			vTarget.z = NormalFunction(vTarget.x);
		}

		break;
	}
	case Right:
	{
		if (vDirection.x < 0.0f)
		{
			vPos.x += fSpeed;
			vTarget.x += fSpeed;
		}
		else if (vDirection.x > 0.0f)
		{
			vPos.x -= fSpeed;
			vTarget.x -= fSpeed;
		}

		if (vDirection.x == 0.0f)
		{
			if (vDirection.z > 0.0f)
			{
				vPos.x -= fSpeed;
				vTarget.x -= fSpeed;
			}
			else
			{
				vPos.x += fSpeed;
				vTarget.x += fSpeed;
			}
		}
		else
		{
			vPos.z = NormalFunction(vPos.x);
			vTarget.z = NormalFunction(vTarget.x);
		}

		break;
	}
	default:
		break;
	}

	vPosPin = vPos;
	vTargetPin = vTarget;

	deltaPos += vPos - temp[0];
	deltaTarget += vTarget - temp[1];

	std::cout << "\ncamera" << std::endl;
	std::cout << vPos.x << "\t" << vPos.y << "\t" << vPos.z << std::endl;
	std::cout << vTarget.x << "\t" << vTarget.y << "\t" << vTarget.z << std::endl;
}

GLvoid Camera::Rotate(GLfloat fSign)
{
	vDegree.x += fSign * 1.0f;

	vPos -= deltaPos;
	vTarget -= deltaTarget;
	vPos.x = (GLfloat)sin(glm::radians(vDegree.x)) * UpdateDistance();
	vPos.z = -(GLfloat)cos(glm::radians(vDegree.x)) * UpdateDistance();
	vPos += deltaPos;
	vTarget += deltaTarget;

	vPosPin = vPos;
	vTargetPin = vTarget;

	std::cout << vDegree.x << std::endl;
}

GLfloat Camera::UpdateDistance()
{
	return sqrtf((GLfloat)pow(vDirection.x, 2) + (GLfloat)pow(vDirection.y, 2) + (GLfloat)pow(vDirection.z, 2));
}
GLfloat Camera::LinearFunction(GLfloat attribX)
{
	return (vDirection.z / vDirection.x) * (attribX - vPosPin.x) + vPosPin.z;
}
GLfloat Camera::NormalFunction(GLfloat attribX)
{
	if (attribX == vPos.x)
		return -(vDirection.x / vDirection.z) * (attribX - vPosPin.x) + vPosPin.z;
	else
		return -(vDirection.x / vDirection.z) * (attribX - vTargetPin.x) + vTargetPin.z;
}