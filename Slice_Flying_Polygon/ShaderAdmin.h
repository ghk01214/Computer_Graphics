#pragma once
#include "define.h"
#include "Shader1D.h"
#include "Shader2D.h"
class ShaderAdmin
{
private:
	BaseShader* bShader;
	Shader1D* s1CutTrack;
	std::pair<Shader2D*, GLbool> pSpace[3][8];
	std::vector<std::pair<BaseShader*, std::pair<GLint, GLint>>> vFlyingPolygon;

	GLint iShaderNum;
	GLchar cAxis;
	GLfloat fSign;

	std::pair<GLfloat, GLfloat> pMouseStart;
	std::pair<GLfloat, GLfloat> pMouseEnd;

	Pos pTempStart;
	Pos pTempEnd;

	std::vector<Pos> vStart;
	std::vector<Pos> vEnd;
	std::vector<GLfloat> vDelta;
	GLint iDirection;

	std::vector<Pos> vFlyingCenter;

	GLfloat fSpeed;
	GLint iShowPath;

	Pos pCrossPoint[2];

public:
	ShaderAdmin();
	~ShaderAdmin();
public:
	GLfloat FindCrossPoint(GLfloat fX, GLint i);
public:
	GLvoid DrawSpace();
	GLvoid MakeShader(GLint iType);
	GLvoid Render();
public:
	GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY);
	GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY);
	GLvoid Motion(GLint iX, GLint iY);
	GLvoid Timer(GLint iValue);
};

