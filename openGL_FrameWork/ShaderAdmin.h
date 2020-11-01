#pragma once
#include "define.h"
#include "Shader1D.h"
#include "Shader2D.h"
#include "Shader3D.h"

class ShaderAdmin
{
private:
	std::vector<BaseShader> vList;
public:
	ShaderAdmin();
	~ShaderAdmin();
public:
	GLvoid MakeShader(GLint);
};

namespace Manage
{
	enum Type
	{
		//��, ��, �ﰢ��, �簢��, �����ü, �簢��, ������ü, ��
		Line, Triangle, Square, Circle, Tetrahedron, Pyramid, Hexahedron, Sphere
	};
}