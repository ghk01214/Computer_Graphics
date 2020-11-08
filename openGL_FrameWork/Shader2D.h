#pragma once
#include "BaseShader.h"

class Shader2D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[Num::VBO];
	GLuint uiEBO;
public:
	Shader2D(GLint);
	~Shader2D();
public:
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid CreateObject(GLint, Pos) override;
};