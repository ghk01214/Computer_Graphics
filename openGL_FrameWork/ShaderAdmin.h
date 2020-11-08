#pragma once
#include "define.h"
#include "Shader1D.h"
#include "Shader2D.h"
#include "Shader3D.h"

class ShaderAdmin
{
private:
	BaseShader* bShader;
	std::vector<std::pair<BaseShader*, std::pair<GLint, Pos>>> vNorm;
	std::vector<std::pair<BaseShader*, std::pair<GLint, Pos>>> vList;
	GLint iShaderNum;
	GLchar cAxis;
	GLfloat fSign;

	//Ä«¸Þ¶ó
	Camera cView;
public:
	ShaderAdmin();
	~ShaderAdmin();
public:
	std::pair<BaseShader*, std::pair<GLint, Pos>> ReturnShader(GLint iShaderNum) { return vList[iShaderNum]; }
public:
	GLvoid MakeShader(GLint, Pos);
	GLvoid Render();
public:
	GLvoid PrintShaderInfo();
public:
	GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY);
	GLvoid Special(GLint iKey, GLint iX, GLint iY);
};

