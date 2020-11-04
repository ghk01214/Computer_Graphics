#pragma once
#include "ShaderAdmin.h"

ShaderAdmin sAdmin;

//�̺�Ʈ�� ���� �� ȣ��Ǵ� �Լ�
GLvoid Idle()
{

}

//Ű���� �Է�
GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = �Է� Ű����
	//iX, iY = Ű���� �Է� �� ���콺 ��ġ

	switch (ubKey)
	{
	//����
	case 'l':
	{

		break;
	}
	//�ﰢ��
	case 't':
	{
		Pos pPos = { 0.0f, 0.0f, 0.0f };
		sAdmin.MakeShader(Manage::Triangle, pPos);

		break;
	}
	//�簢��
	case 's':
	{
		Pos pPos = { 0.0f, 0.0f, 0.0f };
		sAdmin.MakeShader(Manage::Square, pPos);

		break;
	}
	//��
	case 'c':
	{

		break;
	}
	//�����ü
	case 'T':
	{
		Pos pPos = { 0.0f, 0.0f, 0.0f };
		//sAdmin.MakeShader(Manage::Tetrahedron, pPos);

		break;
	}
	case 'P':
	{
		Pos pPos = { 0.0f, 0.0f, 0.0f };
		sAdmin.MakeShader(Manage::Pyramid, pPos);

		break;
	}
	//����
	case 'C':
	{
		Pos pPos = { 0.0f, 0.0f, 0.0f };
		sAdmin.MakeShader(Manage::Cone, pPos);

		break;
	}
	case 'h':
	{
		Pos pPos = { 0.0f, 0.0f, 0.0f };
		sAdmin.MakeShader(Manage::Cube, pPos);

		break;
	}
	//��
	case 'S':
	{
		Pos pPos = { 0.0f, 0.0f, 0.0f };
		sAdmin.MakeShader(Manage::Sphere, pPos);

		break;
	}
	//����
	case 'Q': case 'q':
	{
		exit(0);
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

//ASCII�� �ƴ� Ư�� Ű �Է�
GLvoid Special(GLint iKey, GLint iX, GLint iY)
{
	//ubKey = �Է� Ű����
	//iX, iY = Ű���� �Է� �� ���콺 ��ġ
		
	/*
	KEY_MAP
	GLUT_KEY_F1 ~ GLUT_KEY_F12
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
	GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT, GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN
	*/

	switch (iKey)
	{

	}
}

//Ű���� ����
GLvoid KeyboardUp(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = �Է� Ű����
	//iX, iY = Ű���� �Է� �� ���콺 ��ġ

	switch (ubKey)
	{

	}
}

//ASCII�� �ƴ� Ư�� Ű ����
GLvoid SpecialUp(GLint iKey, GLint iX, GLint iY)
{
	//ubKey = �Է� Ű����
	//iX, iY = Ű���� �Է� �� ���콺 ��ġ

	/*
	KEY_MAP
	GLUT_KEY_F1 ~ GLUT_KEY_F12
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
	GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT, GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN
	*/

	switch (iKey)
	{

	}
}

//���콺 �Է�
GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	//iButton = ��ư �Ķ����(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
	//iState = ���� �Ķ����(GLUT_UP, GLUT_DOWN)
	//iX, iY = ���콺 ��ġ
}

//���콺 ������ �̵�
GLvoid Motion(GLint iX, GLint iY)
{

}

//���콺 ������ �ʰ� �̵�
GLvoid Passive(GLint iX, GLint iY)
{

}

//��� �Լ�
GLvoid DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialUpFunc(SpecialUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(Passive);
}