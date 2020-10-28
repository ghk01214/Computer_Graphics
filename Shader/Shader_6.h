//실습 9번
#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VAO_NUM 4
#define VBO_NUM 8

enum Direction
{
	Left, Bottom, Right, Top
};

class Triangle
{
private:
	GLfloat fPosition[3][3];
	GLfloat fColor[3][3];
	GLint iDirection;
	GLfloat iDelta;
	BOOL bIncrease;
public:
	Triangle(GLint);
	GLvoid Position(GLint);
	GLvoid Move(GLint);
	GLvoid ChangeDirection(GLint);
	GLvoid Resize(GLint);
	GLfloat ReturnPos(GLint, GLint);
	GLfloat ReturnColor(GLint, GLint);
	~Triangle();
};

Triangle::Triangle(GLint i)
{
	Triangle::iDelta = 0.5f;

	//정점 좌표 초기화
	Triangle::fPosition[0][0] = 0.0f;
	Triangle::fPosition[0][1] = 0.0f;
	Triangle::Position(i);

	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uDis(0.0f, 1.0f);

	for (GLint i = 0; i < 3; ++i)
	{
		Triangle::fPosition[i][2] = 0.0f;

		Triangle::fColor[0][i] = 0.0f;
		Triangle::fColor[1][i] = uDis(mGen);
		Triangle::fColor[2][i] = Triangle::fColor[1][i];
	}

	Triangle::iDirection = i;
	Triangle::bIncrease = FALSE;
}
Triangle::~Triangle()
{

}
GLvoid Triangle::Position(GLint i)
{
	switch (i)
	{
	case 0:
	{
		Triangle::fPosition[1][0] = Triangle::fPosition[0][0] - 0.5f;
		Triangle::fPosition[1][1] = Triangle::fPosition[0][1] + Triangle::iDelta;

		Triangle::fPosition[2][0] = Triangle::fPosition[0][0] - 0.5f;
		Triangle::fPosition[2][1] = Triangle::fPosition[0][1] - Triangle::iDelta;

		break;
	}
	case 1:
	{
		Triangle::fPosition[1][0] = Triangle::fPosition[0][0] - Triangle::iDelta;
		Triangle::fPosition[1][1] = Triangle::fPosition[0][1] - 0.5f;

		Triangle::fPosition[2][0] = Triangle::fPosition[0][0] + Triangle::iDelta;
		Triangle::fPosition[2][1] = Triangle::fPosition[0][1] - 0.5f;

		break;
	}
	case 2:
	{
		Triangle::fPosition[1][0] = Triangle::fPosition[0][0] + 0.5f;
		Triangle::fPosition[1][1] = Triangle::fPosition[0][1] - Triangle::iDelta;

		Triangle::fPosition[2][0] = Triangle::fPosition[0][0] + 0.5f;
		Triangle::fPosition[2][1] = Triangle::fPosition[0][1] + Triangle::iDelta;

		break;
	}
	case 3:
	{
		Triangle::fPosition[1][0] = Triangle::fPosition[0][0] + Triangle::iDelta;
		Triangle::fPosition[1][1] = Triangle::fPosition[0][1] + 0.5f;

		Triangle::fPosition[2][0] = Triangle::fPosition[0][0] - Triangle::iDelta;
		Triangle::fPosition[2][1] = Triangle::fPosition[0][1] + 0.5f;

		break;
	}
	default:
		break;
	}
}
GLvoid Triangle::ChangeDirection(GLint i)
{
	switch (i)
	{
	case 0:
	{
		if (Triangle::fPosition[0][0] < -0.5f)
		{
			Triangle::iDirection = Direction::Right;
		}
		else if (Triangle::fPosition[0][0] > 0.0f)
		{
			Triangle::iDirection = Direction::Left;
		}

		break;
	}
	case 1:
	{
		if (Triangle::fPosition[0][1] < -0.5f)
		{
			Triangle::iDirection = Direction::Top;
		}
		else if (Triangle::fPosition[0][1] > 0.0f)
		{
			Triangle::iDirection = Direction::Bottom;
		}

		break;
	}
	case 2:
	{
		if (Triangle::fPosition[0][0] > 0.5f)
		{
			Triangle::iDirection = Direction::Left;
		}
		else if (Triangle::fPosition[0][0] < 0.0f)
		{
			Triangle::iDirection = Direction::Right;
		}

		break;
	}
	case 3:
	{
		if (Triangle::fPosition[0][1] > 0.5f)
		{
			Triangle::iDirection = Direction::Bottom;
		}
		else if (Triangle::fPosition[0][1] < 0.0f)
		{
			Triangle::iDirection = Direction::Top;
		}

		break;
	}
	default:
		break;
	}
}
GLvoid Triangle::Move(GLint i)
{
	Triangle::ChangeDirection(i);

	switch (Triangle::iDirection)
	{
	case Direction::Left:
	{
		Triangle::fPosition[0][0] -= 0.005f;
		break;
	}
	case Direction::Right:
	{
		Triangle::fPosition[0][0] += 0.005f;
		break;
	}
	case Direction::Top:
	{
		Triangle::fPosition[0][1] += 0.005f;
		break;
	}
	case Direction::Bottom:
	{
		Triangle::fPosition[0][1] -= 0.005f;
		break;
	}
	default:
		break;
	}

	Triangle::Position(i);
}
GLvoid Triangle::Resize(GLint i)
{
	if (Triangle::iDelta < 0.0f && !Triangle::bIncrease)
	{
		Triangle::bIncrease = TRUE;
	}
	else if (Triangle::iDelta > 0.5f && Triangle::bIncrease)
	{
		Triangle::bIncrease = FALSE;
	}

	if (Triangle::bIncrease)
	{
		Triangle::iDelta += 0.005f;
	}
	else
	{
		Triangle::iDelta -= 0.005f;
	}

	Triangle::Position(i);
}
GLfloat Triangle::ReturnPos(GLint i, GLint j)
{
	return Triangle::fPosition[i][j];
}
GLfloat Triangle::ReturnColor(GLint i, GLint j)
{
	return Triangle::fColor[i][j];
}

GLuint uiVAO[VAO_NUM];
GLuint uiVBO[VBO_NUM];

Triangle* tTriangle[4];
BOOL bStartTimer = FALSE;

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;
	GLfloat Position[4][3][3], Color[4][3][3];

	if (!bInitialize)
	{
		glGenVertexArrays(VAO_NUM, uiVAO);
		glGenBuffers(VBO_NUM, uiVBO);

		for (GLint i = 0; i < 4; ++i)
		{
			tTriangle[i] = new Triangle(i);
		}

		bInitialize = TRUE;
	}

	for (GLint k = 0; k < 4; ++k)
	{
		for (GLint i = 0; i < 3; ++i)
		{
			for (GLint j = 0; j < 3; ++j)
			{
				Position[k][i][j] = tTriangle[k]->ReturnPos(i, j);
				Color[k][i][j] = tTriangle[k]->ReturnColor(i, j);
			}
		}
	}

	for (GLint i = 0; i < VAO_NUM; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Position[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2 + 1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Color[i], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}

GLvoid Timer(GLint iValue)
{
	if (bStartTimer)
	{
		switch (iValue)
		{
		case 1:
		{
			for (GLint i = 0; i < 4; ++i)
			{
				tTriangle[i]->Move(i);
			}

			break;
		}
		case 2:
		{
			for (GLint i = 0; i < 4; ++i)
			{
				tTriangle[i]->Resize(i);
			}

			break;
		}
		default:
			break;
		}

		glutTimerFunc(1, Timer, iValue);
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
		glutTimerFunc(1, Timer, 1);
		break;
	}
	case 'S': case 's':
	{
		bStartTimer = TRUE;
		glutTimerFunc(1, Timer, 2);
		break;
	}
	case 'Q': case 'q':
	{
		bStartTimer = FALSE;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid SpecialKey(GLint iKey, GLint iX, GLint iY)
{
	switch (iKey)
	{
	case GLUT_KEY_END:
	{
		exit(0);
		for (GLint i = 0; i < 4; ++i)
		{
			delete[] tTriangle[i];
		}
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// 바탕색을 흰색으로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// 설정된 색으로 전체를 칠하기

	glUseProgram(mMaster.ShaderID());

	for (GLint i = 0; i < VAO_NUM; ++i)
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
	glutSpecialFunc(SpecialKey);
	glutMainLoop();														// 이벤트 처리 시작
}