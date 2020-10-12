#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VAO 10
#define VBO 20

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;

	GLfloat Triangle[10][3][3], TriangleColor[10][3][3];

	for (GLint k = 0; k < VAO; ++k)
	{
		for (GLint i = 0; i < 3; ++i)
		{
			for (GLint j = 0; j < 3; ++j)
			{
				Triangle[k][i][j] = oOutside[k].TrianglePos(i, j);
				TriangleColor[k][i][j] = oOutside[k].Color(i, j);
			}
		}
	}

	if (!bInitialize)
	{
		glGenVertexArrays(VAO, uiVAO);
		glGenBuffers(VBO, uiVBO);

		bInitialize = TRUE;
	}

	for (GLint i = 0; i < VAO; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Triangle[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2 + 1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TriangleColor[i], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// 바탕색을 흰색으로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// 설정된 색으로 전체를 칠하기

	GLuint ShaderID = mMaster.ShaderID();
	glUseProgram(ShaderID);

	for (GLint i = 0; i < VAO; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glutSwapBuffers();												// 화면에 출력하기
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