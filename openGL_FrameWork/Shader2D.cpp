#include "Shader2D.h"

Shader2D::Shader2D(GLint k)
{
	pPos = new Pos[k];
	cColor = new Color[k];
	iIndex = new Index[k - 2];

	iVertexNum = k;
	iIndexNum = k - 2;

	glGenBuffers(Num::VBO, uiVBO);
	glGenBuffers(1, &(uiEBO));
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
	Render();
}

GLvoid Shader2D::Render()
{
	glUseProgram(ReturnShaderID());

	TransformShader();

	glBindVertexArray(ReturnVAO());
	glDrawElements(GL_TRIANGLES, iIndexNum * 3, GL_UNSIGNED_INT, 0);
}

GLvoid Shader2D::CreateObject(GLint iType, Pos pCenter)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uDis(0.0f, 1.0f);

	switch (iType)
	{
	case Manage::Triangle:
	{
		//삼각형
		pPos[0] = { pCenter.X, pCenter.Y + 0.2f, pCenter.Z };
		pPos[1] = { pCenter.X - 0.17f, pCenter.Y - 0.1f, pCenter.Z };
		pPos[2] = { pCenter.X + 0.17f, pCenter.Y - 0.1f, pCenter.Z };

		cColor[0] = { 1.0f, 0.0f, 0.0f };
		cColor[1] = { 0.0f, 1.0f, 0.0f };
		cColor[2] = { 0.0f, 0.0f, 1.0f };

		iIndex[0] = { 0, 1, 2 };

		break;
	}
	case Manage::Square:
	{
		//사각형
		pPos[0] = { pCenter.X - 0.2f, pCenter.Y + 0.2f, pCenter.Z };
		pPos[1] = { pCenter.X - 0.2f, pCenter.Y - 0.2f, pCenter.Z };
		pPos[2] = { pCenter.X + 0.2f, pCenter.Y - 0.2f, pCenter.Z };
		pPos[3] = { pCenter.X + 0.2f, pCenter.Y + 0.2f, pCenter.Z };

		cColor[0] = { 1.0f, 0.0f, 0.0f };
		cColor[1] = { 0.0f, 1.0f, 0.0f };
		cColor[2] = { 0.0f, 0.0f, 1.0f };
		cColor[3] = { 0.0f, 0.0f, 0.0f };

		iIndex[0] = { 0, 1, 2 };
		iIndex[1] = { 0, 2, 3 };

		break;
	}
	default:
		break;
	}

	InitializeBuffer();
}

Shader2D::~Shader2D()
{
	delete[] pPos;
	delete[] cColor;
	delete[] iIndex;
}