#include "Shader1D.h"

Shader1D::Shader1D(GLint k)
{
	pPos = new Pos[k];
	cColor = new Color[k];

	iVertexNum = k;
	
	glGenBuffers(Num::VBO, uiVBO);
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
	Render();
}

GLvoid Shader1D::Render()
{
	glUseProgram(ReturnShaderID());

	glBindVertexArray(uiVAO);
	glDrawArrays(GL_LINES, 0, 2);
}

GLvoid Shader1D::CreateObject(GLint iType, Pos pCenter)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uDis(0.0f, 1.0f);

	switch (iType)
	{
	case Manage::X:
	{
		pPos[0] = { pCenter.X + 5.0f, pCenter.Y, pCenter.Z };
		pPos[1] = { pCenter.X - 5.0f, pCenter.Y, pCenter.Z };

		for (GLint i = 0; i < 2; ++i)
		{
			cColor[i] = { 1.0f, 1.0f, 1.0f };
		}

		break;
	}
	case Manage::Y:
	{
		pPos[0] = { pCenter.X, pCenter.Y + 5.0f, pCenter.Z };
		pPos[1] = { pCenter.X, pCenter.Y - 5.0f, pCenter.Z };

		for (GLint i = 0; i < 2; ++i)
		{
			cColor[i] = { 0.0f, 1.0f, 0.0f };
		}

		break;
	}
	case Manage::Z:
	{
		pPos[0] = { pCenter.X, pCenter.Y, pCenter.Z + 5.0f };
		pPos[1] = { pCenter.X, pCenter.Y, pCenter.Z - 5.0f };

		for (GLint i = 0; i < 2; ++i)
		{
			cColor[i] = { 0.0f, 0.0f, 1.0f };
		}

		break;
	}
	default:
		break;
	}

	InitializeBuffer();
}

Shader1D::~Shader1D()
{
	delete[] pPos;
	delete[] cColor;
	delete[] iIndex;
}