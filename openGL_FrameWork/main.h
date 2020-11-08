#pragma once
#include "ShaderAdmin.h"

ShaderAdmin sAdmin;

//이벤트가 없을 때 호출되는 함수
GLvoid Idle()
{

}

//키보드 입력
GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치

	sAdmin.Keyboard(ubKey, iX, iY);

	switch (ubKey)
	{
	case 'l':
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}
	case 'f':
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
	//종료
	case 'Q': case 'q':
	{
		exit(0);
		break;
	}
	}

	glutPostRedisplay();
}

//ASCII가 아닌 특수 키 입력
GLvoid Special(GLint iKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치
		
	/*
	KEY_MAP
	GLUT_KEY_F1 ~ GLUT_KEY_F12
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
	GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT, GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN
	*/

	sAdmin.Special(iKey, iX, iY);

	glutPostRedisplay();
}

//키보드 떼기
GLvoid KeyboardUp(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치


	glutPostRedisplay();
}

//ASCII가 아닌 특수 키 떼기
GLvoid SpecialUp(GLint iKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치

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

//마우스 입력
GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	//iButton = 버튼 파라미터(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
	//iState = 상태 파라미터(GLUT_UP, GLUT_DOWN)
	//iX, iY = 마우스 위치
}

//마우스 누르고 이동
GLvoid Motion(GLint iX, GLint iY)
{

}

//마우스 누르지 않고 이동
GLvoid Passive(GLint iX, GLint iY)
{

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
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialUpFunc(SpecialUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(Passive);
}