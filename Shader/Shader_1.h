#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct Position
{
	GLfloat iX, iY;
} Pos;

GLuint uiVAO[4], uiVBO[8];

Pos pTrianglePos[4] =
{
	{0.5, 0.5},
	{-0.5, 0.5},
	{-0.5, -0.5},
	{0.5, -0.5}
};
GLfloat cfTriangle[4][3][3] =
{
	{
		{pTrianglePos[0].iX - 0.2, pTrianglePos[0].iY - 0.2, 0.0},
		{pTrianglePos[0].iX + 0.2, pTrianglePos[0].iY - 0.2, 0.0},
		{pTrianglePos[0].iX, pTrianglePos[0].iY + 0.2, 0.0},
	},
	{
		{pTrianglePos[1].iX - 0.2, pTrianglePos[1].iY - 0.2, 0.0},
		{pTrianglePos[1].iX + 0.2, pTrianglePos[1].iY - 0.2, 0.0},
		{pTrianglePos[1].iX, pTrianglePos[1].iY + 0.2, 0.0},
	},
	{
		{pTrianglePos[2].iX - 0.2, pTrianglePos[2].iY - 0.2, 0.0},
		{pTrianglePos[2].iX + 0.2, pTrianglePos[2].iY - 0.2, 0.0},
		{pTrianglePos[2].iX, pTrianglePos[2].iY + 0.2, 0.0},
	},
	{
		{pTrianglePos[3].iX - 0.2, pTrianglePos[3].iY - 0.2, 0.0},
		{pTrianglePos[3].iX + 0.2, pTrianglePos[3].iY - 0.2, 0.0},
		{pTrianglePos[3].iX, pTrianglePos[3].iY + 0.2, 0.0},
	}
};
const GLfloat cfColor[4][3][3] =
{
	{
		{1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
	},
	{
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
	},
	{
		{0.0, 0.0, 1.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, 1.0},
	},
	{
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0},
	}
};

GLvoid FuctionalizeGlut()
{
	glutDisplayFunc(DrawScene);											// 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);											// 다시 그리기 콜백함수 지정
	glutMouseFunc(Mouse);
	glutMainLoop();														// 이벤트 처리 시작
}

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;

	if (!bInitialize)
	{
		glGenVertexArrays(4, uiVAO);
		glGenBuffers(8, uiVBO);

		bInitialize = TRUE;
	}

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

GLvoid ChangePos(GLint i)
{
	cfTriangle[i][0][0] = pTrianglePos[0].iX - 0.2;
	cfTriangle[i][0][1] = pTrianglePos[0].iY - 0.2;

	cfTriangle[i][1][0] = pTrianglePos[0].iX + 0.2;
	cfTriangle[i][1][1] = pTrianglePos[0].iY - 0.2;

	cfTriangle[i][2][0] = pTrianglePos[0].iX;
	cfTriangle[i][2][1] = pTrianglePos[0].iY + 0.2;
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

GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	static GLint i = 0;

	if (iButton == GLUT_LEFT_BUTTON && iState == GLUT_DOWN)
	{
		pTrianglePos[i].iX = (GLfloat)(iX - WINDOW_WIDTH / 2) / (WINDOW_WIDTH / 2);
		pTrianglePos[i].iY = (GLfloat)(WINDOW_HEIGHT / 2 - iY) / (WINDOW_HEIGHT / 2);

		ChangePos(i);

		i = (i + 1) % 4;
	}

	InitializeBuffer();
	glutPostRedisplay();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)							// 콜백 함수 : 다시 그리기 콜백 함수
{
	glViewport(0, 0, iWidth, iHeight);
}