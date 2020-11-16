#include "Shader1D.h"

Shader1D::Shader1D(GLint k)
{
	pPos = new Pos[k];
	cColor = new Color[k];

	iVertexNum = k;

	glGenBuffers(Num::VBO, uiVBO);
}

GLvoid Shader1D::InputPos(Pos pPos, GLint i)
{
	this->pPos[i] = pPos;
}
GLvoid Shader1D::InputColor(Color cColor)
{
	for (GLint i = 0; i < iVertexNum; ++i)
	{
		this->cColor[i] = cColor;
	}
}

GLvoid Shader1D::CreateObject(GLint iType, GLint iDirection)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());

	switch (iType)
	{
	case Manage::Line:
	{
		if (pPos[1].X < -2.0f || pPos[1].X > 2.0f)
		{
			switch (iDirection)
			{
			case Num::RT:
			{
				std::uniform_real_distribution<GLfloat> uDis(1.0f, 2.0f);
				pPos[1] = { uDis(mGen), uDis(mGen), 0.0f };

				break;
			}
			case Num::LT:
			{
				std::uniform_real_distribution<GLfloat> uDisX(-2.0f, -1.0f);
				std::uniform_real_distribution<GLfloat> uDisY(1.0f, 2.0f);
				pPos[1] = { uDisX(mGen), uDisY(mGen), 0.0f };

				break;
			}
			case Num::RB:
			{
				std::uniform_real_distribution<GLfloat> uDisX(1.0f, 2.0f);
				std::uniform_real_distribution<GLfloat> uDisY(-0.42f, 0.58f);
				pPos[1] = { uDisX(mGen), uDisY(mGen), 0.0f };

				break;
			}
			case Num::LB:
			{
				std::uniform_real_distribution<GLfloat> uDisX(-2.0f, -1.0f);
				std::uniform_real_distribution<GLfloat> uDisY(-0.42f, 0.58f);
				pPos[1] = { uDisX(mGen), uDisY(mGen), 0.0f };

				break;
			}
			default:
				break;
			}
		}

		if (cColor->R < 0.0f || cColor->R > 1.0f)
		{
			cColor[0] = { 0.0f, 0.0f, 0.0f };
			cColor[1] = { 0.0f, 0.0f, 0.0f };
		}
		
		break;
	}
	default:
		break;
	}

	InitializeBuffer();
}

GLvoid Shader1D::InitializeBuffer()
{
	uiVAO = ReturnVAO();

	glBindVertexArray(uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, iVertexNum * sizeof(Pos), pPos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, iVertexNum * sizeof(Color), cColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	InputVAO(uiVAO);
}

GLvoid Shader1D::Render()
{
	glUseProgram(ReturnShaderID());

	glBindVertexArray(uiVAO);
	glDrawArrays(GL_LINES, 0, 2);
}

Shader1D::~Shader1D()
{
	delete[] pPos;
	delete[] cColor;
}