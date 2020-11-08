#include "Shader3D.h"

Shader3D::Shader3D(GLint k)
{
	pPos = new Pos[k];
	cColor = new Color[k];
	iIndex = new Index[2 * k - 4];

	glGenBuffers(Num::VBO, uiVBO);
	glGenBuffers(1, &(uiEBO));
}

GLvoid Shader3D::InitializeBuffer()
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

GLvoid Shader3D::Render()
{
	glUseProgram(ReturnShaderID());

	TransformShader();
	glEnable(GL_DEPTH_TEST);

	glBindVertexArray(uiVAO);
	glDrawElements(GL_TRIANGLES, iIndexNum * 3, GL_UNSIGNED_INT, 0);
}

GLvoid Shader3D::CreateObject(GLint iType, Pos pCenter)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uDis(0.0f, 1.0f);
	FILE* fObj;

	switch (iType)
	{
	case Manage::Cube:
	{
		fObj = fopen("cube.txt", "r");

		cColor[0] = { 0.0f, 1.0f, 1.0f };
		cColor[1] = { 0.0f, 0.0f, 1.0f };
		cColor[2] = { 1.0f, 0.0f, 1.0f };
		cColor[3] = { 1.0f, 1.0f, 1.0f };
		cColor[4] = { 0.0f, 1.0f, 0.0f };
		cColor[5] = { 0.0f, 0.0f, 0.0f };
		cColor[6] = { 1.0f, 0.0f, 0.0f };
		cColor[7] = { 1.0f, 1.0f, 0.0f };

		break;
	}
	case Manage::Cone:
	{
		fObj = fopen("cone.txt", "r");
		vSize = glm::vec3(2.0f, 2.0f, 2.0f);

		break;
	}
	case Manage::Sphere:
	{
		fObj = fopen("sphere.txt", "r");
		vSize = glm::vec3(0.1f, 0.1f, 0.1f);

		break;
	}
	default:
		break;
	}

	ReadObj(fObj);

	//새로운 셰이더에 색상이 없으면 정점별 랜덤 색상을 한 번만 할당
	if (cColor[0].R < 0.0f || cColor[0].R > 1.0f)
	{
		for (GLint i = 0; i < iVertexNum; ++i)
		{
			cColor[i] = { uDis(mGen), uDis(mGen), uDis(mGen) };
		}
	}

	InitializeBuffer();
}

Shader3D::~Shader3D()
{

}