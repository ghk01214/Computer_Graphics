#pragma once
#include "BaseShader.h"

class Shader2D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[NUM::VBO];
	GLuint uiEBO;
public:
	Shader2D(GLint);
	~Shader2D();
public:
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	GLvoid InitializeProgram();
public:
	virtual GLvoid MakePolygon(GLint, Pos) override;
};