#pragma once
#include "define.h"
#include "Shader1D.h"
#include "Shader2D.h"
#include "Shader3D.h"

class ShaderAdmin
{
private:
	BaseShader* bShader;
	std::vector<std::pair<BaseShader*, std::pair<GLint, Pos>>> vList;
public:
	ShaderAdmin();
	~ShaderAdmin();
public:
	GLvoid MakeShader(GLint, Pos);
	GLvoid Render();
};

