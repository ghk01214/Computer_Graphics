//실습 6번
#include "Shader.h"

GLuint uiVAO[10], uiVBO[10];

GLvoid FuctionalizeGlut()
{
	glutDisplayFunc(DrawScene);											// 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);											// 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(1, Timer, 1);
	glutMainLoop();														// 이벤트 처리 시작
}

GLvoid InitializeBuffer()
{
	for (GLint i = 0; i < 4; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfTriangle[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2 + 1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfColor[i], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// 바탕색을 흰색으로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// 설정된 색으로 전체를 칠하기

	glUseProgram(mMaster.ShaderID());

	for (int i = 0; i < 4; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Timer(GLint iValue)
{
	if (mMaster.StartTimer())
	{

		InitializeBuffer();
		glutTimerFunc(1, Timer, 1);
	}

	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case '1': case VK_NUMPAD1:
	{

		break;
	}
	case '2': case VK_NUMPAD2:
	{

		break;
	}
	case '3': case VK_NUMPAD3:
	{

		break;
	}
	case 'Q': case 'q':
	{
		glutDestroyWindow(1);
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	static GLint i = 0;

	if (iButton == GLUT_LEFT_BUTTON && iState == GLUT_DOWN)
	{

	}

	InitializeBuffer();
	glutPostRedisplay();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)							// 콜백 함수 : 다시 그리기 콜백 함수
{
	glViewport(0, 0, iWidth, iHeight);
}