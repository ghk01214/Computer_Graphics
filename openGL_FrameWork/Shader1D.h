#pragma once
#include "BaseShader.h"

class Shader1D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[Num::VBO];
public:
	Shader1D(GLint);
	~Shader1D();
public:
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid CreateObject(GLint, Pos) override;
};