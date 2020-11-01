#include "Shader2D.h"

Shader2D::Shader2D(GLint k)
{
	this->pPos = new Pos[k];
	this->cColor = new Color[k];
	this->iIndex = new Index[k - 2];

	this->iVertexNum = k;
	this->iIndexNum = k - 2;

	glGenBuffers(NUM::VBO, this->uiVBO);
	glGenBuffers(1, &(this->uiEBO));
}

GLvoid Shader2D::InitializeBuffer()
{
	this->uiVAO = this->ReturnVAO();

	glBindVertexArray(this->uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, this->iVertexNum * sizeof(Pos), this->pPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->iIndexNum * sizeof(Index), this->iIndex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, this->uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, this->iVertexNum * sizeof(Color), this->cColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	this->InputVAO(this->uiVAO);
	this->Render();
}

GLvoid Shader2D::Render()
{
	glUseProgram(this->ReturnShaderID());

	glBindVertexArray(this->ReturnVAO());
	glDrawElements(GL_TRIANGLES, this->iIndexNum * 3, GL_UNSIGNED_INT, 0);
}

GLvoid Shader2D::InitializeProgram()
{

}

GLvoid Shader2D::MakePolygon(GLint iType, Pos pCenter)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uDis(0.0f, 1.0f);

	switch (iType)
	{
	case 3:
	{
		//삼각형
		this->pPos[0] = { pCenter.X, pCenter.Y + 0.2f, pCenter.Z };
		this->pPos[1] = { pCenter.X - 0.17f, pCenter.Y - 0.1f, pCenter.Z };
		this->pPos[2] = { pCenter.X + 0.17f, pCenter.Y - 0.1f, pCenter.Z };

		this->cColor[0] = { 1.0f, 0.0f, 0.0f };
		this->cColor[1] = { 0.0f, 1.0f, 0.0f };
		this->cColor[2] = { 0.0f, 0.0f, 1.0f };

		this->iIndex[0] = { 0, 1, 2 };

		break;
	}
	case 4:
	{
		//사각형
		this->pPos[0] = { pCenter.X - 0.2f, pCenter.Y + 0.2f, pCenter.Z };
		this->pPos[1] = { pCenter.X - 0.2f, pCenter.Y - 0.2f, pCenter.Z };
		this->pPos[2] = { pCenter.X + 0.2f, pCenter.Y - 0.2f, pCenter.Z };
		this->pPos[3] = { pCenter.X + 0.2f, pCenter.Y + 0.2f, pCenter.Z };

		this->cColor[0] = { 1.0f, 0.0f, 0.0f };
		this->cColor[1] = { 0.0f, 1.0f, 0.0f };
		this->cColor[2] = { 0.0f, 0.0f, 1.0f };
		this->cColor[3] = { 0.0f, 0.0f, 0.0f };

		this->iIndex[0] = { 0, 1, 2 };
		this->iIndex[1] = { 0, 1, 3 };


		break;
	}
	default:
		break;
	}

	this->InitializeBuffer();
}

Shader2D::~Shader2D()
{
	delete[] this->pPos;
	delete[] this->cColor;
	delete[] this->iIndex;
}