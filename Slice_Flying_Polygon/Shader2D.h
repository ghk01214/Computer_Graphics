#pragma once
#include "BaseShader.h"

class Shader2D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[Num::VBO];
	GLuint uiEBO;
	
	Pos pCenter;
	std::vector<Color> vColor;
public:
	Shader2D(GLint);
	~Shader2D();
public:
	virtual Pos ReturnPos(GLint i) override { return pPos[i]; }
	virtual Pos ReturnCenter() override { return pCenter; }
public:
	virtual GLvoid InputPos(Pos pPos, GLint i) override;
	virtual GLvoid InputColor(Color cColor) override;
	virtual GLvoid InputCenter(Pos tempCenter) override { pCenter = tempCenter; }
public:
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid CreateObject(GLint iType, GLint iDirection) override;
};