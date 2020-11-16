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
	
	std::vector<std::pair<BaseShader*, BaseShader*>> vCutPolygon;
	std::vector<std::pair<Pos, Pos>> vCutCenter;

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
	GLint iCutPolygonNum;

	BaseShader* tempShader[2];
	Pos tempCenter[2];
	GLbool bCutTimer;

public:
	ShaderAdmin();
	~ShaderAdmin();
public:
	GLvoid FindCrossPoint();
public:
	GLvoid DrawSpace();
	GLvoid MakeShader(GLint iType);
	GLvoid Render();

	GLvoid MovePolygon(GLint iSign, GLint i);
	GLvoid DeleteShader(GLint i);
public:
	GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY);
	GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY);
	GLvoid Motion(GLint iX, GLint iY);
	GLvoid TimerFunc(GLint iValue);
	GLvoid Timer(GLint iValue);
	GLvoid FallTimer(GLint iValue);
public:
	GLbool ReturnCutTimer() { return bCutTimer; }
};