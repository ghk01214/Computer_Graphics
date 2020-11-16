#pragma once
#include "ShaderAdmin.h"

ShaderAdmin sAdmin;

//키보드 입력
GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	sAdmin.Keyboard(ubKey, iX, iY);
}

//마우스 입력
GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	sAdmin.Mouse(iButton, iState, iX, iY);
}

//마우스 누르고 이동
GLvoid Motion(GLint iX, GLint iY)
{
	sAdmin.Motion(iX, iY);
}

GLvoid Timer(GLint iValue)
{
	sAdmin.Timer(iValue);

	glutTimerFunc(50, Timer, 1);
}

GLvoid TimerFunc(GLint iValue)
{
	sAdmin.TimerFunc(iValue);

	glutTimerFunc(4000, TimerFunc, 1);
}

GLvoid FallTimer(GLint iValue)
{
	if (sAdmin.ReturnCutTimer())
		sAdmin.FallTimer(iValue);

	glutTimerFunc(50, FallTimer, 2);
}

GLvoid DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sAdmin.Render();

	glutSwapBuffers();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)
{
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid CallBackFunc()
{
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(1, Timer, 1);
	glutTimerFunc(50, TimerFunc, 0);
	glutTimerFunc(50, FallTimer, 2);
}