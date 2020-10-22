//실습 10번
#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VAO_NUM 4
#define VBO_NUM 8
#define EBO_NUM 1

class Object
{
private:
	GLfloat Position[5][3];
	GLfloat Color[5][3];
	GLuint Index[3][3];
	GLfloat iDelta;
public:
	Object(GLint);
	GLvoid Expand(GLint);
	GLfloat ReturnPos(GLint, GLint);
	GLfloat ReturnColor(GLint, GLint);
	GLuint ReturnIndex(GLint, GLint);
	~Object();
};

Object::Object(GLint k)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uDis(0.0f, 1.0f);

	//정점별 컬러 초기화
	for (GLint i = 0; i < 5; ++i)
	{
		Object::Position[i][2] = 0.0f;

		for (GLint j = 0; j < 3; ++j)
		{
			Object::Color[i][j] = uDis(mGen);
		}
	}

	//좌표 초기화
	switch (k)
	{
	case 3:
	{
		Object::Position[0][0] = -0.8f;
		Object::Position[1][0] = -0.2f;
		Object::Position[2][0] = -0.5f;

		for (GLint i = 0; i < 3; ++i)
		{
			Object::Position[i][1] = 0.2f;
		}

		for (GLint i = 0; i < 3; ++i)
		{
			Object::Index[0][i] = i;
		}

		break;
	}
	case 4:
	{
		Object::Position[0][0] = 0.5f;
		Object::Position[0][1] = 0.8f;

		Object::Position[1][0] = 0.2f;
		Object::Position[1][1] = 0.2f;

		Object::Position[2][0] = 0.8f;
		Object::Position[2][1] = 0.2f;

		Object::Position[3][0] = 0.5f;
		Object::Position[3][1] = 0.8f;

		for (GLuint i = 0; i < 3; ++i)
		{
			Object::Index[0][i] = i;
		}

		Object::Index[1][0] = 0;

		for (GLuint i = 1; i < 3; ++i)
		{
			Object::Index[1][i] = i + 1;
		}

		break;
	}
	case 5:
	{
		Object::Position[0][0] = -0.7f;
		Object::Position[0][1] = -0.5f;

		Object::Position[1][0] = -0.7f;
		Object::Position[1][1] = -0.7f;

		Object::Position[2][0] = -0.3f;
		Object::Position[2][1] = -0.7f;

		Object::Position[3][0] = -0.3f;
		Object::Position[3][1] = -0.5f;

		Object::Position[4][0] = -0.5f;
		Object::Position[4][1] = -0.5f;

		for (GLint i = 0; i < 3; ++i)
		{
			Object::Index[0][i] = i;
			Object::Index[i][0] = 0;
		}

		for (GLint i = 1; i < 3; ++i)
		{
			for (GLint j = 1; j < 3; ++j)
			{
				Object::Index[i][j] = i + j;
			}
		}

		break;
	}
	case 6:
	{
		Object::Position[0][0] = 0.2f;
		Object::Position[0][1] = -0.5f;

		Object::Position[1][0] = 0.3f;
		Object::Position[1][1] = -0.8f;

		Object::Position[2][0] = 0.7f;
		Object::Position[2][1] = -0.8f;

		Object::Position[3][0] = 0.8f;
		Object::Position[3][1] = -0.5f;

		Object::Position[4][0] = 0.5f;
		Object::Position[4][1] = -0.2f;

		for (GLint i = 0; i < 3; ++i)
		{
			Object::Index[0][i] = i;
			Object::Index[i][0] = 0;
		}

		for (GLint i = 1; i < 3; ++i)
		{
			for (GLint j = 1; j < 3; ++j)
			{
				Object::Index[i][j] = i + j;
			}
		}
	}
	default:
		break;
	}

	Object::iDelta = 0.005f;
}
GLvoid Object::Expand(GLint k)
{
	switch (k)
	{
	case 3:
	{
		if (Object::Position[2][1] > 0.8f)
		{
			Object::Position[2][1] = 0.3f;
		}
		else
		{
			Object::Position[2][1] += Object::iDelta;
		}

		break;
	}
	case 4:
	{
		if (Object::Position[0][0] < 0.3f)
		{
			Object::Position[0][0] = 0.5f;
			Object::Position[3][0] = 0.5f;
		}
		else
		{
			Object::Position[0][0] -= Object::iDelta;
			Object::Position[3][0] += Object::iDelta;
		}

		break;
	}
	case 5:
	{
		if (Object::Position[4][1] > -0.2f)
		{
			Object::Position[4][1] = -0.5f;
		}
		else
		{
			Object::Position[4][1] += Object::iDelta;
		}

		break;
	}
	case 6:
	{
		static GLfloat iTemp = 0;

		if (iTemp > 0.2f)
		{
			Object::Position[0][0] = 0.2f;
			Object::Position[0][1] = -0.5f;

			Object::Position[1][0] = 0.3f;
			Object::Position[1][1] = -0.8f;

			Object::Position[2][0] = 0.7f;
			Object::Position[2][1] = -0.8f;

			Object::Position[3][0] = 0.8f;
			Object::Position[3][1] = -0.5f;

			Object::Position[4][0] = 0.5f;
			Object::Position[4][1] = -0.2f;

			iTemp = Object::iDelta;
		}
		else
		{

			for (GLint i = 0; i < 2; ++i)
			{
				Object::Position[i][0] += Object::iDelta;
			}

			for (GLint i = 2; i < 4; ++i)
			{
				Object::Position[i][0] -= Object::iDelta;
			}

			for (GLint i = 1; i < 3; ++i)
			{
				Object::Position[i][1] += Object::iDelta;
			}

			Object::Position[4][1] -= Object::iDelta;

			iTemp += Object::iDelta;
		}

		break;
	}
	default:
		break;
	}
}
GLfloat Object::ReturnPos(GLint i, GLint j)
{
	return Object::Position[i][j];
}
GLfloat Object::ReturnColor(GLint i, GLint j)
{
	return Object::Color[i][j];
}
GLuint Object::ReturnIndex(GLint i, GLint j)
{
	return Object::Index[i][j];
}
Object::~Object()
{

}

Object* oObject[4];

GLuint uiVAO[VAO_NUM];
GLuint uiVBO[VBO_NUM];
GLuint uiEBO;

BOOL bStartTimer = FALSE;

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;
	GLfloat TriInfo[2][3][3], RectPos[4][3], PentaInfo[2][2][5][3];				//[종류(1: 좌표, 2: 컬러)][정점 개수][X, Y, Z/R, G, B]
	GLuint TriIndex[3], RectIndex[2][3], PentaIndex[2][3][3];
	GLfloat RectColor[4][3];

	if (!bInitialize)
	{
		glGenVertexArrays(VAO_NUM, uiVAO);
		glGenBuffers(VBO_NUM, uiVBO);
		glGenBuffers(EBO_NUM, &uiEBO);

		for (GLint i = 0; i < 4; ++i)
		{
			oObject[i] = new Object(i + 3);
		}

		bInitialize = TRUE;
	}

	for (GLint i = 0; i < 3; ++i)
	{
		for (GLint j = 0; j < 3; ++j)
		{
			TriInfo[0][i][j] = oObject[0]->ReturnPos(i, j);
			TriInfo[1][i][j] = oObject[0]->ReturnColor(i, j);
		}

		TriIndex[i] = oObject[0]->ReturnIndex(0, i);
	}

	for (GLint i = 0; i < 4; ++i)
	{
		for (GLint j = 0; j < 3; ++j)
		{
			RectPos[i][j] = oObject[1]->ReturnPos(i, j);
			RectColor[i][j] = oObject[1]->ReturnColor(i, j);

			if (i < 2)
			{
				RectIndex[i][j] = oObject[1]->ReturnIndex(i, j);
			}
		}
	}

	for (GLint k = 0; k < 2; ++k)
	{
		for (GLint i = 0; i < 5; ++i)
		{
			for (GLint j = 0; j < 3; ++j)
			{
				PentaInfo[k][0][i][j] = oObject[k + 2]->ReturnPos(i, j);
				PentaInfo[k][1][i][j] = oObject[k + 2]->ReturnColor(i, j);

				if (i < 3)
				{
					PentaIndex[k][i][j] = oObject[k + 2]->ReturnIndex(i, j);
				}
			}
		}
	}

	//2사분면
	glBindVertexArray(uiVAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TriInfo[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), TriIndex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TriInfo[1], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//1사분면
	glBindVertexArray(uiVAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), RectPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), RectIndex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), RectColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//3&4사분면
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
		for (GLint i = 0; i < 4; ++i)
		{
			oObject[i]->Expand(i + 3);
		}

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
		for (GLint i = 0; i < 4; ++i)
		{
			delete oObject[i];
		}

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
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(uiVAO[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	for (GLint i = VAO_NUM - 2; i < VAO_NUM; ++i)
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