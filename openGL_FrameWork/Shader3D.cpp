#include "pch.h"
#include "Shader3D.h"

Shader3D::Shader3D()
{
}

Shader3D::~Shader3D()
{
}

GLvoid Shader3D::CreateObject(GLint iType)
{
	return GLvoid();
}

GLvoid Shader3D::CreateObject(GLint iType, glm::vec3 color)
{
	FILE* fObj = GLM_NULLPTR;

	switch (iType)
	{
	case Cube:
	{
		fObj = fopen("cube.txt", "r");

		break;
	}
	case Sphere:
	{
		fObj = fopen("sphere.txt", "r");

		break;
	}
	case Cone:
	{
		fObj = fopen("cone.txt", "r");

		break;
	}
	default:
		break;
	}

	ReadObj(fObj);

	for (GLint i = 0; i < vertexNum; ++i)
	{
		vColor[i] = color;
	}

	InitializeBuffer();
}