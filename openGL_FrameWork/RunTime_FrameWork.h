#pragma once
#include "Shader2D.h"
#include "Shader3D.h"
#include "Camera.h"
#include "Player.h"

class RunTime_FrameWork
{
private:
	BaseShader* bShader;
	Player* pPlayer;
	Camera cView;
	GLint viewPoint;

	std::vector<BaseShader*> vList;
public:
	RunTime_FrameWork();
	~RunTime_FrameWork();
public:
	GLvoid MakeShader();
	GLvoid Render();
public:
	GLvoid KeyboardDown(GLubyte key, GLint x, GLint y);
	GLvoid SpecialKeyDown(GLint key, GLint x, GLint y);
public:
	enum View
	{
		Front, Back, Top
	};
};