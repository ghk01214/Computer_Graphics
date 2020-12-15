#include "pch.h"
#include "Player.h"

Player::Player()
{
	vPos = glm::vec3(0.0f, 0.0f, 0.0f);
	vTarget = glm::vec3(0.0f, 0.0f, 5.0f);
	vDirection = vTarget - vPos;

	deltaPos = glm::vec3(0.0f, 0.0f, 0.0f);
	deltaTarget = glm::vec3(0.0f, 0.0f, 0.0f);

	fDegree = 0.0f;
}

Player::Player(Camera cView)
{
	vPos = cView.ReturnPos();
	vTarget = cView.ReturnTarget();
	vDirection = vTarget - vPos;

	deltaPos = glm::vec3(0.0f, 0.0f, 0.0f);
	deltaTarget = glm::vec3(0.0f, 0.0f, 0.0f);

	fDegree = 0.0f;

	std::cout << "\nplayer" << std::endl;
	std::cout << vPos.x << "\t" << vPos.y << "\t" << vPos.z << std::endl;
	std::cout << vTarget.x << "\t" << vTarget.y << "\t" << vTarget.z << std::endl;
}

Player::~Player()
{
}

GLvoid Player::ModelPlayer(Camera cView)
{
	ModelHead(cView);
	ModelBody(cView);
	ModelArms(cView);
	ModelLegs(cView);
}
GLvoid Player::ModelHead(Camera cView)
{
	bShader = new Shader3D();
	bShader->CreateObject(bShader->Sphere, glm::vec3(0.0f, 1.0f, 0.0f));

	bShader->Scale(glm::vec3(0.07f, 0.07f, 0.07f));
	bShader->Translate(glm::vec3(0.0f, 15.0f, 0.5f));
	bShader->View(cView);

	vPart.push_back(bShader);
}
GLvoid Player::ModelBody(Camera cView)
{
	bShader = new Shader3D();
	bShader->CreateObject(bShader->Cube, glm::vec3(0.0f, 0.0f, 1.0f));

	bShader->Scale(glm::vec3(1.3f, 2.0f, 0.8f));
	bShader->Translate(glm::vec3(0.0f, -0.2f, 0.0f));
	bShader->View(cView);
	//vPos = bShader->ReturnOnePos(0);

	vPart.push_back(bShader);
}
GLvoid Player::ModelArms(Camera cView)
{
	bShader = new Shader3D();
	bShader->CreateObject(bShader->Cube, glm::vec3(1.0f, 1.0f, 0.0f));

	bShader->Scale(glm::vec3(0.5f, 1.3f, 0.6f));
	bShader->Translate(glm::vec3(1.8f, -0.2f, 0.0f));
	bShader->View(cView);

	vPart.push_back(bShader);

	bShader = new Shader3D();
	bShader->CreateObject(bShader->Cube, glm::vec3(1.0f, 1.0f, 0.0f));

	bShader->Scale(glm::vec3(0.5f, 1.3f, 0.6f));
	bShader->Translate(glm::vec3(-1.8f, -0.2f, 0.0f));
	bShader->View(cView);

	vPart.push_back(bShader);
}
GLvoid Player::ModelLegs(Camera cView)
{
	bShader = new Shader3D();
	bShader->CreateObject(bShader->Cube, glm::vec3(1.0f, 1.0f, 1.0f));

	bShader->Scale(glm::vec3(0.5f, 1.3f, 0.6f));
	bShader->Translate(glm::vec3(0.6f, -1.5f, 0.0f));
	bShader->View(cView);

	vPart.push_back(bShader);

	bShader = new Shader3D();
	bShader->CreateObject(bShader->Cube, glm::vec3(1.0f, 1.0f, 1.0f));

	bShader->Scale(glm::vec3(0.5f, 1.3f, 0.6f));
	bShader->Translate(glm::vec3(-0.6f, -1.5f, 0.0f));
	bShader->View(cView);

	vPart.push_back(bShader);
}

GLvoid Player::Move(GLint iDirection, GLfloat fSpeed)
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

			MoveObject(fSpeed, -1, GL_TRUE);
		}
		else if (vDirection.x > 0.0f)
		{
			vPos.x += fSpeed;
			vTarget.x += fSpeed;

			MoveObject(fSpeed, 1, GL_TRUE);
		}

		if (vDirection.x == 0.0f)
		{
			if (vDirection.z > 0.0f)
			{
				vPos.z += fSpeed;
				vTarget.z += fSpeed;

				MoveObject(fSpeed, 1, GL_FALSE);
			}
			else
			{
				vPos.z -= fSpeed;
				vTarget.z -= fSpeed;

				MoveObject(fSpeed, -1, GL_FALSE);
			}
		}
		else
		{
			vPos.z = LinearFunction(vPos.x);
			vTarget.z = LinearFunction(vTarget.x);

			MoveObject((vPos.z - temp[0].z) * vDirection.z, 1, GL_FALSE);
		}

		break;
	}
	case Backward:
	{
		if (vDirection.x < 0.0f)
		{
			vPos.x += fSpeed;
			vTarget.x += fSpeed;

			MoveObject(fSpeed, 1, GL_TRUE);
		}
		else if (vDirection.x > 0.0f)
		{
			vPos.x -= fSpeed;
			vTarget.x -= fSpeed;

			MoveObject(fSpeed, -1, GL_TRUE);
		}

		if (vDirection.x == 0.0f)
		{
			if (vDirection.z > 0.0f)
			{
				vPos.z -= fSpeed;
				vTarget.z -= fSpeed;

				MoveObject(fSpeed, -1, GL_FALSE);
			}
			else
			{
				vPos.z += fSpeed;
				vTarget.z += fSpeed;

				MoveObject(fSpeed, 1, GL_FALSE);
			}
		}
		else
		{
			vPos.z = LinearFunction(vPos.x);
			vTarget.z = LinearFunction(vTarget.x);

			MoveObject((vPos.z - temp[0].z) * vDirection.z, 1, GL_FALSE);
		}

		break;
	}
	case Left:
	{
		if (vDirection.x < 0.0f)
		{
			vPos.x -= fSpeed;
			vTarget.x -= fSpeed;

			MoveObject(fSpeed, -1, GL_TRUE);
		}
		else if (vDirection.x > 0.0f)
		{
			vPos.x += fSpeed;
			vTarget.x += fSpeed;

			MoveObject(fSpeed, 1, GL_TRUE);
		}

		if (vDirection.x == 0.0f)
		{
			if (vDirection.z > 0.0f)
			{
				vPos.x += fSpeed;
				vTarget.x += fSpeed;

				MoveObject(fSpeed, 1, GL_TRUE);
			}
			else
			{
				vPos.x -= fSpeed;
				vTarget.x -= fSpeed;

				MoveObject(fSpeed, -1, GL_TRUE);
			}
		}
		else
		{
			vPos.z = NormalFunction(vPos.x);
			vTarget.z = NormalFunction(vTarget.x);

			MoveObject((vPos.z - temp[0].z)* vDirection.z, 1, GL_FALSE);
		}

		break;
	}
	case Right:
	{
		if (vDirection.x < 0.0f)
		{
			vPos.x += fSpeed;
			vTarget.x += fSpeed;

			MoveObject(fSpeed, 1, GL_TRUE);
		}
		else if (vDirection.x > 0.0f)
		{
			vPos.x -= fSpeed;
			vTarget.x -= fSpeed;

			MoveObject(fSpeed, -1, GL_TRUE);
		}

		if (vDirection.x == 0.0f)
		{
			if (vDirection.z > 0.0f)
			{
				vPos.x -= fSpeed;
				vTarget.x -= fSpeed;

				MoveObject(fSpeed, -1, GL_TRUE);
			}
			else
			{
				vPos.x += fSpeed;
				vTarget.x += fSpeed;

				MoveObject(fSpeed, 1, GL_TRUE);
			}
		}
		else
		{
			vPos.z = NormalFunction(vPos.x);
			vTarget.z = NormalFunction(vTarget.x);

			MoveObject((vPos.z - temp[0].z)* vDirection.z, 1, GL_FALSE);
		}

		break;
	}
	default:
		break;
	}

	std::cout << "\nplayer" << std::endl;
	std::cout << vPos.x << "\t" << vPos.y << "\t" << vPos.z << std::endl;
	std::cout << vTarget.x << "\t" << vTarget.y << "\t" << vTarget.z << std::endl;

	vPosPin = vPos;
	vTargetPin = vTarget;

	deltaPos += vPos - temp[0];
	deltaTarget += vTarget - temp[1];
}
GLvoid Player::MoveObject(GLfloat fSpeed, GLfloat fSign, GLbool x)
{
	if (x)
	{
		vPart[0]->Translate(glm::vec3(fSign * fSpeed * 19.5f, 0.0f, 0.0f));
		vPart[1]->Translate(glm::vec3(fSign * fSpeed * 1.05f, 0.0f, 0.0f));
		vPart[2]->Translate(glm::vec3(fSign * fSpeed * 2.73f, 0.0f, 0.0f));
		vPart[3]->Translate(glm::vec3(fSign * fSpeed * 2.73f, 0.0f, 0.0f));
		vPart[4]->Translate(glm::vec3(fSign * fSpeed * 2.73f, 0.0f, 0.0f));
		vPart[5]->Translate(glm::vec3(fSign * fSpeed * 2.73f, 0.0f, 0.0f));
	}
	else
	{
		vPart[0]->Translate(glm::vec3(0.0f, 0.0f, fSign * fSpeed * 19.5f));
		vPart[1]->Translate(glm::vec3(0.0f, 0.0f, fSign * fSpeed * 1.706f));
		vPart[2]->Translate(glm::vec3(0.0f, 0.0f, fSign * fSpeed * 2.275f));
		vPart[3]->Translate(glm::vec3(0.0f, 0.0f, fSign * fSpeed * 2.275f));
		vPart[4]->Translate(glm::vec3(0.0f, 0.0f, fSign * fSpeed * 2.275f));
		vPart[5]->Translate(glm::vec3(0.0f, 0.0f, fSign * fSpeed * 2.275f));
	}
}

GLvoid Player::Rotate(GLfloat fSign)
{
	fDegree += fSign * 1.0f;

	vPos -= deltaPos;
	vTarget -= deltaTarget;
	vPos.x = (GLfloat)sin(glm::radians(fDegree)) * UpdateDistance();
	vPos.z = -(GLfloat)cos(glm::radians(fDegree)) * UpdateDistance();
	vPos += deltaPos;
	vTarget += deltaTarget;

	vPart[0]->Translate(glm::vec3(0.0f, -15.0f, -0.5f));
	vPart[0]->Scale(glm::vec3(1 / 0.07f, 1 / 0.07f, 1 / 0.07f));
	vPart[0]->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), fSign * 1.0f);
	vPart[0]->Scale(glm::vec3(0.07f, 0.07f, 0.07f));
	vPart[0]->Translate(glm::vec3(0.0f, 15.0f, 0.5f));

	vPart[1]->Translate(glm::vec3(0.0f, 0.2f, 0.0f));
	vPart[1]->Scale(glm::vec3(1 / 1.3f, 1 / 2.0f, 1 / 0.8f));
	vPart[1]->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), fSign * 1.0f);
	vPart[1]->Scale(glm::vec3(1.3f, 2.0f, 0.8f));
	vPart[1]->Translate(glm::vec3(0.0f, -0.2f, 0.0f));

	vPart[2]->Translate(glm::vec3(-1.8f, 0.2f, 0.0f));
	vPart[2]->Scale(glm::vec3(1 / 0.5f, 1 / 1.3f, 1 / 0.6f));
	vPart[2]->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), fSign * 1.0f);
	vPart[2]->Scale(glm::vec3(0.5f, 1.3f, 0.6f));
	vPart[2]->Translate(glm::vec3(1.8f, -0.2f, 0.0f));

	vPart[3]->Translate(glm::vec3(1.8f, 0.2f, 0.0f));
	vPart[3]->Scale(glm::vec3(1 / 0.5f, 1 / 1.3f, 1 / 0.6f));
	vPart[3]->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), fSign * 1.0f);
	vPart[3]->Scale(glm::vec3(0.5f, 1.3f, 0.6f));
	vPart[3]->Translate(glm::vec3(-1.8f, -0.2f, 0.0f));

	vPart[4]->Translate(glm::vec3(-0.6f, 0.0f, 0.0f));
	vPart[4]->Scale(glm::vec3(1 / 0.5f, 1 / 1.3f, 1 / 0.6f));
	vPart[4]->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), fSign * 1.0f);
	vPart[4]->Scale(glm::vec3(0.5f, 1.3f, 0.6f));
	vPart[4]->Translate(glm::vec3(0.6f, 0.0f, 0.0f));

	vPart[5]->Translate(glm::vec3(0.6f, -1.5f, 0.0f));
	vPart[5]->Scale(glm::vec3(1 / 0.5f, 1 / 1.3f, 1 / 0.6f));
	vPart[5]->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), fSign * 1.0f);
	vPart[5]->Scale(glm::vec3(0.5f, 1.3f, 0.6f));
	vPart[5]->Translate(glm::vec3(-0.6f, 1.5f, 0.0f));

	vPosPin = vPos;
	vTargetPin = vTarget;

	std::cout << "\nplayer" << std::endl;
	std::cout << vPos.x << "\t" << vPos.y << "\t" << vPos.z << std::endl;
	std::cout << vTarget.x << "\t" << vTarget.y << "\t" << vTarget.z << std::endl;
}

GLvoid Player::View(Camera cView)
{
	for (GLint i = 0; i < vPart.size(); ++i)
	{
		vPart[i]->View(cView);
	}
}

GLfloat Player::UpdateDistance()
{
	return sqrtf((GLfloat)pow(vDirection.x, 2) + (GLfloat)pow(vDirection.y, 2) + (GLfloat)pow(vDirection.z, 2));
}
GLfloat Player::LinearFunction(GLfloat attribX)
{
	return (vDirection.z / vDirection.x) * (attribX - vPosPin.x) + vPosPin.z;
}
GLfloat Player::NormalFunction(GLfloat attribX)
{
	if (attribX == vPos.x)
		return -(vDirection.x / vDirection.z) * (attribX - vPosPin.x) + vPosPin.z;
	else
		return -(vDirection.x / vDirection.z) * (attribX - vTargetPin.x) + vTargetPin.z;
}

GLvoid Player::Render()
{
	for (GLint i = 0; i < vPart.size(); ++i)
	{
		vPart[i]->Render();
	}
}