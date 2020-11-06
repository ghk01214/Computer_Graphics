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
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid MakePolygon(GLint, Pos) override;

	virtual GLvoid KeyDown(GLubyte ubKey, GLint iX, GLint iY) override;
	virtual GLvoid KeyUp(GLubyte ubKey, GLint iX, GLint iY) override;
	virtual GLvoid SpecialDown(GLint iKey, GLint iX, GLint iY) override;
	virtual GLvoid SpecialUp(GLint iKey, GLint iX, GLint iY) override;
};