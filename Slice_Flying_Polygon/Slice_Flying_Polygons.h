#pragma once
#include "ShaderAdmin.h"

ShaderAdmin sAdmin;

//키보드 입력
GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치

	sAdmin.Keyboard(ubKey, iX, iY);
}

//마우스 입력
GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	//iButton = 버튼 파라미터(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
	//iState = 상태 파라미터(GLUT_UP, GLUT_DOWN)
	//iX, iY = 마우스 위치

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
	glutTimerFunc(1, Timer, 1);
}

//출력 함수
GLvoid DrawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sAdmin.Render();

	glutSwapBuffers();
}

//화면 크기 변화 이벤트 처리 함수
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
}