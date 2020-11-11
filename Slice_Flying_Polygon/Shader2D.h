#pragma once
#include "BaseShader.h"

class Shader2D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[Num::VBO];
	GLuint uiEBO;
	Pos pBarycenter;
public:
	Shader2D(GLint);
	~Shader2D();
public:
	virtual GLvoid InputBarycenter(Pos pBarycenter) override {};
	virtual Pos ReturnBarycenter() override { return pBarycenter; }
public:
	virtual GLvoid InputPos(Pos pPos, GLint i) override;
	virtual GLvoid InputColor(Color cColor) override;
public:
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid CreateObject(GLint iType, GLint iDirection) override;
};