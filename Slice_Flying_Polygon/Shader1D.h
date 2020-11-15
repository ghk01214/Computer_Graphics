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
	virtual GLvoid InputPos(Pos pPos, GLint i) override;
	virtual GLvoid InputColor(Color cColor) override;
	virtual GLvoid InputCenter(Pos) override {};
public:
	virtual Pos ReturnPos(GLint i) override { return pPos[i]; }
	virtual Pos ReturnCenter() override { Pos temp; return temp; }
public:
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid CreateObject(GLint iType, GLint iDirection) override;
};