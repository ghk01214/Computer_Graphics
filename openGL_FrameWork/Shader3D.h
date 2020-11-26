#pragma once
#include "BaseShader.h"

class Shader3D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[Num::VBO];
	GLuint uiEBO;
public:
	Shader3D(GLint k);
	~Shader3D();
public:
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid CreateObject(GLint iType, Pos pCenter) override;
};