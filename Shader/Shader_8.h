//실습 11번
#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VAO_NUM 4
#define VBO_NUM 8

struct Pos
{
	GLfloat fX, fY, fZ;
};

struct Color
{
	GLfloat fR, fG, fB;
};

class Rect
{
private:
	Pos pPos[5];
	Color cColor[5];
	GLuint fIndex[4][3];
public:
	Rect();
	Pos ReturnPos(GLint);
	Color ReturnColor(GLint);
	GLuint ReturnIndex(GLint, GLint);
	GLvoid Resize(GLfloat, GLfloat);
	~Rect();
};

Rect::Rect()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uDis(0.0f, 1.0f);

	Rect::pPos[0].fX = 0.0f;
	Rect::pPos[0].fY = 0.0f;

	Rect::pPos[1].fX = -0.5f;
	Rect::pPos[1].fY = 0.5f;

	Rect::pPos[2].fX = -0.5f;
	Rect::pPos[2].fY = -0.5f;

	Rect::pPos[3].fX = 0.5f;
	Rect::pPos[3].fY = -0.5f;

	Rect::pPos[4].fX = 0.5f;
	Rect::pPos[4].fY = 0.5f;

	for (GLint i = 0; i < 5; ++i)
	{
		Rect::pPos[i].fZ = 0.0f;

		Rect::cColor[i].fR = uDis(mGen);
		Rect::cColor[i].fG = uDis(mGen);
		Rect::cColor[i].fB = uDis(mGen);
	}

	for (GLint i = 0; i < 4; ++i)
	{
		Rect::fIndex[i][0] = 0;

		for (GLint j = 1; j < 3; ++j)
		{
			Rect::fIndex[i][j] = i + j;
		}
	}

	Rect::fIndex[3][2] = 1;
}
Pos Rect::ReturnPos(GLint i)
{
	return Rect::pPos[i];
}
Color Rect::ReturnColor(GLint i)
{
	return Rect::cColor[i];
}
GLuint Rect::ReturnIndex(GLint i, GLint j)
{
	return Rect::fIndex[i][j];
}
GLvoid Rect::Resize(GLfloat fX, GLfloat fY)
{
	for (GLint i = 1; i < 5; ++i)
	{
		if (fX >= Rect::pPos[i].fX - 0.1f && fX <= Rect::pPos[i].fX + 0.1f)
		{
			if (fY >= Rect::pPos[i].fY - 0.1f && fY <= Rect::pPos[i].fY + 0.1f)
			{
				GLfloat dX = fX - Rect::pPos[i].fX;
				GLfloat dY = fY - Rect::pPos[i].fY;

				Rect::pPos[i].fX += dX;
				Rect::pPos[i].fY += dY;

				Rect::pPos[i].fX += dX;
				Rect::pPos[i].fY += dY;
			}
		}
	}
}
Rect::~Rect()
{

}

GLuint uiVAO[VAO_NUM];
GLuint uiVBO[VBO_NUM];
GLuint uiEBO;

Rect rRect;

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;
	Pos TriPos[5];
	Color TriColor[5];
	GLuint Index[4][3];

	if (!bInitialize)
	{
		glGenVertexArrays(VAO_NUM, uiVAO);
		glGenBuffers(VBO_NUM, uiVBO);
		glGenBuffers(1, &uiEBO);

		bInitialize = TRUE;
	}

	for (GLint i = 0; i < 5; ++i)
	{
		TriPos[i] = rRect.ReturnPos(i);
		TriColor[i] = rRect.ReturnColor(i);

		if (i < 4)
		{
			for (GLint j = 0; j < 3; ++j)
			{
				Index[i][j] = rRect.ReturnIndex(i, j);
			}
		}
	}

	glBindVertexArray(uiVAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), TriPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(GLuint), Index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(GLfloat), TriColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	if (iButton == GLUT_LEFT_BUTTON && iState == GLUT_DOWN)
	{
		GLfloat glPos[2] = { (GLfloat)(iX - WINDOW_WIDTH / 2) / (WINDOW_WIDTH / 2), (GLfloat)(WINDOW_HEIGHT / 2 - iY) / (WINDOW_HEIGHT / 2) };
		
		rRect.Resize(glPos[0], glPos[1]);


	}

	InitializeBuffer();
	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'T': case 't':
	{
		break;
	}
	case 'S': case 's':
	{

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

	glBindVertexArray(uiVAO[0]);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

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
	glutMouseFunc(Mouse);
	glutMainLoop();														// 이벤트 처리 시작
}