#pragma once
#include "BaseShader.h"

class Shader1D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[NUM::VBO];
	GLuint uiEBO;
public:
	Shader1D(GLint);
	~Shader1D();
public:
	GLvoid InitializeProgram();
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
};