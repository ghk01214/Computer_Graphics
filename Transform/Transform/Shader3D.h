#pragma once
#include "BaseShader.h"
#define PYRAMID 1
#define HEXA 2

class Shader3D : public BaseShader
{
private:
	GLuint uiVBO[2];
	Pos* pPos;
	Color* cColor;
	Index* iIndex;

	GLint iVertexNum;
public:
	Shader3D();
	~Shader3D();
public:
	GLvoid DrawPolygon(Pos, GLint);
	GLvoid DrawPyramid(Pos);
	GLvoid DrawHexahedron(Pos);
	GLvoid InitializeAttribute(GLint);
};