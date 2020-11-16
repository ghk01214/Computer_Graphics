#include "Shader2D.h"

Shader2D::Shader2D(GLint k)
{
	pPos = new Pos[k];
	cColor = new Color[k];
	iIndex = new Index[k - 2];

	iVertexNum = k;
	iIndexNum = k - 2;
	pCenter = { -10.0f, -10.0f, -10.0f };

	vColor.push_back({ 0.0f, 0.0f, 0.0f });
	vColor.push_back({ 0.0f, 0.0f, 1.0f });
	vColor.push_back({ 0.0f, 1.0f, 1.0f });
	vColor.push_back({ 1.0f, 0.0f, 0.0f });
	vColor.push_back({ 1.0f, 1.0f, 0.0f });
	vColor.push_back({ 1.0f, 0.0f, 1.0f });

	glGenBuffers(Num::VBO, uiVBO);
	glGenBuffers(1, &(uiEBO));
}

GLvoid Shader2D::InputPos(Pos pPos, GLint i)
{
	this->pPos[i] = pPos;
}
GLvoid Shader2D::InputColor(Color cColor)
{
	for (GLint i = 0; i < iVertexNum; ++i)
	{
		this->cColor[i] = cColor;
	}
}

GLvoid Shader2D::CreateObject(GLint iType, GLint iDirection)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());

	if (pCenter.X == -10.0f)
	{
		switch (iDirection)
		{
		case Num::RT:
		{
			std::uniform_real_distribution<GLfloat> uDisX(-2.0f, -1.0f);
			std::uniform_real_distribution<GLfloat> uDisY(-0.42f, 0.58f);
			pCenter = { uDisX(mGen), uDisY(mGen), 0.0f };

			break;
		}
		case Num::LT:
		{
			std::uniform_real_distribution<GLfloat> uDisX(1.0f, 2.0f);
			std::uniform_real_distribution<GLfloat> uDisY(-0.42f, 0.58f);
			pCenter = { uDisX(mGen), uDisY(mGen), 0.0f };

			break;
		}
		case Num::RB:
		{
			std::uniform_real_distribution<GLfloat> uDisX(-2.0f, -1.0f);
			std::uniform_real_distribution<GLfloat> uDisY(0.0f, 1.0f);
			pCenter = { uDisX(mGen), uDisY(mGen), 0.0f };

			break;
		}
		case Num::LB:
		{
			std::uniform_real_distribution<GLfloat> uDisX(1.0f, 2.0f);
			std::uniform_real_distribution<GLfloat> uDisY(0.0f, 1.0f);
			pCenter = { uDisX(mGen), uDisY(mGen), 0.0f };

			break;
		}
		default:
			break;
		}
	}

	switch (iType)
	{
	case Manage::Triangle:
	{
		pPos[0] = { pCenter.X, pCenter.Y + 0.2f, 0.0f };
		pPos[1] = { pCenter.X - 0.15f, pCenter.Y - 0.1f, 0.0f };
		pPos[2] = { pCenter.X + 0.15f, pCenter.Y - 0.1f, 0.0f };

		iIndex[0] = { 0, 1, 2 };

		break;
	}
	case Manage::Square:
	{
		if (pCenter.Y > -0.58)
		{
			pPos[0] = { pCenter.X - 0.15f, pCenter.Y + 0.15f, 0.0f };
			pPos[1] = { pCenter.X - 0.15f, pCenter.Y - 0.15f, 0.0f };
			pPos[2] = { pCenter.X + 0.15f, pCenter.Y - 0.15f, 0.0f };
			pPos[3] = { pCenter.X + 0.15f, pCenter.Y + 0.15f, 0.0f };
		}

		iIndex[0] = { 0, 1, 2 };
		iIndex[1] = { 0, 2, 3 };

		break;
	}
	default:
		break;
	}

	if (cColor->R < 0.0f || cColor->R > 1.0f)
	{
		std::uniform_int_distribution<GLint> uDis(0, 6);
		GLint iTemp = uDis(mGen);

		for (GLint i = 0; i < iVertexNum; ++i)
		{
			cColor[i] = vColor[iTemp];
		}
	}

	InitializeBuffer();
}

GLvoid Shader2D::InitializeBuffer()
{
	uiVAO = ReturnVAO();

	glBindVertexArray(uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, iVertexNum * sizeof(Pos), pPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iIndexNum * sizeof(Index), iIndex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, iVertexNum * sizeof(Color), cColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	InputVAO(uiVAO);
}
GLvoid Shader2D::Render()
{
	glUseProgram(ReturnShaderID());

	glBindVertexArray(ReturnVAO());
	glDrawElements(GL_TRIANGLES, iIndexNum * 3, GL_UNSIGNED_INT, 0);
}

Shader2D::~Shader2D()
{
	delete[] pPos;
	delete[] cColor;
	delete[] iIndex;
}