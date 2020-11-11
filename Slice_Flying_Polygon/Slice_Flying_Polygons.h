#pragma once
#include "ShaderAdmin.h"

ShaderAdmin sAdmin;

//Ű���� �Է�
GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = �Է� Ű����
	//iX, iY = Ű���� �Է� �� ���콺 ��ġ

	sAdmin.Keyboard(ubKey, iX, iY);
}

//���콺 �Է�
GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	//iButton = ��ư �Ķ����(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
	//iState = ���� �Ķ����(GLUT_UP, GLUT_DOWN)
	//iX, iY = ���콺 ��ġ

	sAdmin.Mouse(iButton, iState, iX, iY);
}

//���콺 ������ �̵�
GLvoid Motion(GLint iX, GLint iY)
{
	sAdmin.Motion(iX, iY);
}

GLvoid Timer(GLint iValue)
{
	sAdmin.Timer(iValue);
	glutTimerFunc(1, Timer, 1);
}

//��� �Լ�
GLvoid DrawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sAdmin.Render();

	glutSwapBuffers();
}

//ȭ�� ũ�� ��ȭ �̺�Ʈ ó�� �Լ�
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