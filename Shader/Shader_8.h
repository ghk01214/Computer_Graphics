//실습 11번
#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VAO_NUM 4
#define VBO_NUM 8
#define EBO_NUM 1

GLuint uiVAO[VAO_NUM];
GLuint uiVBO[VBO_NUM];
GLuint uiEBO;

BOOL bStartTimer = FALSE;

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;

	if (!bInitialize)
	{
		glGenVertexArrays(VAO_NUM, uiVAO);
		glGenBuffers(VBO_NUM, uiVBO);
		glGenBuffers(EBO_NUM, &uiEBO);

		bInitialize = TRUE;
	}

	for (GLint i = 0; i < 2; ++i)
	{
		glBindVertexArray(uiVAO[i + 2]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2 + 4]);
		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), PentaInfo[i][0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(GLuint), PentaIndex[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2 + 5]);
		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), PentaInfo[i][1], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}

GLvoid Timer(GLint iValue)
{
	if (bStartTimer)
	{

		glutTimerFunc(1, Timer, 1);
		InitializeBuffer();
		glutPostRedisplay();
	}
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'T': case 't':
	{
		bStartTimer = TRUE;
		Timer(1);
		break;
	}
	case 'S': case 's':
	{
		bStartTimer = FALSE;
		break;
	}
	case 'Q': case 'q':
	{

		exit(0);
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(mMaster.ShaderID());

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (GLint i = 0; i < VAO_NUM; ++i)
	{
		glBindVertexArray(uiVAO[i]);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	}

	glutSwapBuffers();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)							// 콜백 함수 : 다시 그리기 콜백 함수
{
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid FuctionalizeGlut()
{
	glutDisplayFunc(DrawScene);											// 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);											// 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(1, Timer, 1);
	glutMainLoop();														// 이벤트 처리 시작
}