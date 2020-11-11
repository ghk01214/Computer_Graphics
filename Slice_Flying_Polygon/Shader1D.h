#pragma once
#include "BaseShader.h"

class Shader1D : public BaseShader
{
private:
	GLuint uiVAO;
	GLuint uiVBO[Num::VBO];
	Pos temp;
public:
	Shader1D(GLint);
	~Shader1D();
public:
	virtual Pos ReturnBarycenter() override { return temp; };
	virtual GLvoid InputBarycenter(Pos pBarycenter) override
	{
		if (pPos[0].X < -2.0f || pPos[0].X > 2.0f)
			pPos[0] = pBarycenter;
	}

	virtual GLvoid InputPos(Pos pPos, GLint i) override;
	virtual GLvoid InputColor(Color cColor) override;
public:
	virtual GLvoid InitializeBuffer() override;
	virtual GLvoid Render() override;
public:
	virtual GLvoid CreateObject(GLint iType, GLint iDirection) override;
};