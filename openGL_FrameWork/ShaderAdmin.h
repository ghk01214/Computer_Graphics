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
		//점, 선, 삼각형, 사각형, 정사면체, 사각뿔, 정육면체, 구
		Line, Triangle, Square, Circle, Tetrahedron, Pyramid, Hexahedron, Sphere
	};
}