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
	virtual GLvoid MakePolygon(GLint, Pos) override;

	virtual GLvoid KeyDown(GLubyte, GLint, GLint) override;
	virtual GLvoid KeyUp(GLubyte, GLint, GLint) override;
	virtual GLvoid SpecialDown(GLint, GLint, GLint) override;
	virtual GLvoid SpecialUp(GLint, GLint, GLint) override;
};