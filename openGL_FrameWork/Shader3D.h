#pragma once
#include "BaseShader.h"

class Shader3D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[NUM::VBO];
	GLuint uiEBO;
public:
	Shader3D(GLint);
	~Shader3D();
public:
	GLvoid InitializeProgram();
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid MakePolygon(GLint, Pos) override;
};