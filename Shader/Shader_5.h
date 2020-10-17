//실습 8번
#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VAO_NUM 13
#define VBO_NUM 25

typedef struct Position
{
	GLfloat iX, iY, iZ;
} Pos;

//상단 꼭지점의 방향
enum Direction
{
	Top, Right, Bottom, Left
};

class Object
{
private:
	Pos pTriangleCenter;
	GLfloat fTrianglePos[3][3];
	GLfloat fColor[3][3];
	GLint iMovingDirection;										//삼각형이 움직이는 방향
	GLint iDrawDirection;										//삼각형이 그려지는 방향
	BOOL bStartTimer;
public:
	Object(GLint);
	GLfloat TrianglePos(GLint, GLint);
	GLvoid ChangePos();
	GLfloat Color(GLint, GLint);
	GLvoid ChangeColor();
	GLvoid ChangeDirection(GLint);
	BOOL StartTimer();
	GLvoid ChangeTimer(GLint);
	~Object();
};

Object::Object(GLint i)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uRealDis(-1.0f, 1.0f);
	std::uniform_int_distribution<GLint> uIntDis(Top, Left);

	switch (i)
	{
	case 0:
	{
		do
		{
			Object::pTriangleCenter.iX = uRealDis(mGen);

		} while (Object::pTriangleCenter.iX > -0.4f && Object::pTriangleCenter.iX < 0.4f);

		do
		{
			Object::pTriangleCenter.iY = uRealDis(mGen);
		} while (Object::pTriangleCenter.iY > -0.4f && Object::pTriangleCenter.iY < 0.4f);


		if (Object::pTriangleCenter.iY < -0.4f && Object::pTriangleCenter.iY > -0.65f)
		{
			Object::iMovingDirection = Direction::Bottom;
			Object::iDrawDirection = Direction::Bottom;
		}
		else if (Object::pTriangleCenter.iY < -0.65f)
		{
			Object::iMovingDirection = Direction::Left;
			Object::iDrawDirection = Direction::Top;
		}
		else if (Object::pTriangleCenter.iY > 0.4f && Object::pTriangleCenter.iY < 0.65f)
		{
			Object::iMovingDirection = Direction::Top;
			Object::iDrawDirection = Direction::Top;
		}
		else if (Object::pTriangleCenter.iY > 0.65f)
		{
			Object::iMovingDirection = Direction::Right;
			Object::iDrawDirection = Direction::Bottom;
		}

		if (Object::pTriangleCenter.iX < -0.4f && Object::pTriangleCenter.iX > -0.65f)
		{
			Object::iMovingDirection = Direction::Left;
			Object::iDrawDirection = Direction::Left;
		}
		else if (Object::pTriangleCenter.iX < -0.65f)
		{
			Object::iMovingDirection = Direction::Top;
			Object::iDrawDirection = Direction::Right;
		}
		else if (Object::pTriangleCenter.iX > 0.4f && Object::pTriangleCenter.iX < 0.65f)
		{
			Object::iMovingDirection = Direction::Right;
			Object::iDrawDirection = Direction::Right;
		}
		else if (Object::pTriangleCenter.iX > 0.65f)
		{
			Object::iMovingDirection = Direction::Bottom;
			Object::iDrawDirection = Direction::Left;
		}

		break;
	}
	case 1:
	{
		Object::pTriangleCenter.iX = 0.0f;
		Object::pTriangleCenter.iY = -0.3f;
		Object::iMovingDirection = Direction::Left;
		Object::iDrawDirection = Direction::Top;

		break;
	}
	case 2:
	{
		Object::pTriangleCenter.iX = 0.0f;
		Object::pTriangleCenter.iY = 0.3f;
		Object::iMovingDirection = Direction::Right;
		Object::iDrawDirection = Direction::Bottom;

		break;
	}
	default:
		break;
	}

	Object::pTriangleCenter.iZ = 1.0f;

	Object::ChangeColor();
	Object::ChangePos();

	Object::bStartTimer = FALSE;
}
GLfloat Object::TrianglePos(GLint i, GLint j)
{
	return Object::fTrianglePos[i][j];
}
GLvoid Object::ChangePos()
{
	switch (Object::iMovingDirection)
	{
	case Direction::Left:
	{
		Object::pTriangleCenter.iX -= 0.005f;
		Object::pTriangleCenter.iY += 0.005f;

		break;
	}
	case Direction::Top:
	{
		Object::pTriangleCenter.iX += 0.005f;
		Object::pTriangleCenter.iY += 0.005f;

		break;
	}
	case Direction::Right:
	{
		Object::pTriangleCenter.iX += 0.005f;
		Object::pTriangleCenter.iY -= 0.005f;

		break;
	}
	case Direction::Bottom:
	{
		Object::pTriangleCenter.iX -= 0.005f;
		Object::pTriangleCenter.iY -= 0.005f;

		break;
	}
	default:
		break;
	}

	switch (Object::iDrawDirection)
	{
	case Direction::Top:
	{
		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + pow(-1, i + 1) * 0.1f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY - 0.1f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY + 0.25f;

		break;
	}
	case Direction::Right:
	{

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX - 0.1f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + pow(-1, i + 1) * 0.1f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX + 0.25f;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY;

		break;
	}
	case Direction::Bottom:
	{
		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + pow(-1, i) * 0.1f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + 0.1f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY - 0.25f;

		break;
	}
	case Direction::Left:
	{
		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + 0.1f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + pow(-1, i) * 0.1f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX - 0.25f;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY;

		break;
	}
	default:
		break;
	}

	for (GLint i = 0; i < 3; ++i)
	{
		Object::fTrianglePos[i][2] = 0.0f;
	}
}
GLfloat Object::Color(GLint i, GLint j)
{
	return Object::fColor[i][j];
}
GLvoid Object::ChangeColor()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uRealDis(0.0f, 1.0f);

	for (GLint i = 0; i < 3; ++i)
	{
		for (GLint j = 0; j < 3; ++j)
		{
			Object::fColor[i][j] = uRealDis(mGen);
		}
	}
}
GLvoid Object::ChangeDirection(GLint i)
{
	if (i == 0)
	{
		if (Object::fTrianglePos[0][0] < -1.0f && Object::iMovingDirection != Direction::Top)
		{
			Object::iMovingDirection = Direction::Top;
			Object::iDrawDirection = Direction::Right;
			Object::ChangeColor();
		}
		else if (Object::fTrianglePos[0][1] > 0.8f && Object::iMovingDirection != Direction::Right)
		{
			Object::iMovingDirection = Direction::Right;
			Object::iDrawDirection = Direction::Bottom;
			Object::ChangeColor();
		}
		else if (Object::fTrianglePos[0][0] > 1.0f && Object::iMovingDirection != Direction::Bottom)
		{
			Object::iMovingDirection = Direction::Bottom;
			Object::iDrawDirection = Direction::Left;
			Object::ChangeColor();
		}
		else if (Object::fTrianglePos[0][1] < -0.8f && Object::iMovingDirection != Direction::Left)
		{
			Object::iMovingDirection = Direction::Left;
			Object::iDrawDirection = Direction::Top;
			Object::ChangeColor();
		}

		//내부 사각형 접촉
		if (Object::fTrianglePos[2][0] > -0.4f && Object::fTrianglePos[2][0] < 0.4f)
		{
			if (Object::fTrianglePos[2][1] > -0.4f && Object::iMovingDirection == Direction::Left && Object::iDrawDirection == Direction::Top)
			{
				Object::iMovingDirection = Direction::Bottom;
				Object::iDrawDirection = Direction::Bottom;
				Object::ChangeColor();
			}
			else if (Object::fTrianglePos[2][1] < -1.0f && Object::iMovingDirection == Direction::Bottom && Object::iDrawDirection == Direction::Bottom)
			{
				Object::iMovingDirection = Direction::Left;
				Object::iDrawDirection = Direction::Top;
				Object::ChangeColor();
			}
			else if (Object::fTrianglePos[2][1] < 0.4f && Object::iMovingDirection == Direction::Right && Object::iDrawDirection == Direction::Bottom)
			{
				Object::iMovingDirection = Direction::Top;
				Object::iDrawDirection = Direction::Top;
				Object::ChangeColor();
			}
			else if (Object::fTrianglePos[2][1] > 1.0f && Object::iMovingDirection == Direction::Top && Object::iDrawDirection == Direction::Top)
			{
				Object::iMovingDirection = Direction::Right;
				Object::iDrawDirection = Direction::Bottom;
				Object::ChangeColor();
			}
		}
		if (Object::fTrianglePos[2][1] > -0.4f && Object::fTrianglePos[2][1] < 0.4f)
		{
			if (Object::fTrianglePos[2][0] > -0.4f && Object::iMovingDirection == Direction::Top && Object::iDrawDirection == Direction::Right)
			{
				Object::iMovingDirection = Direction::Left;
				Object::iDrawDirection = Direction::Left;
				Object::ChangeColor();
			}
			else if (Object::fTrianglePos[2][0] < -1.0f && Object::iMovingDirection == Direction::Left && Object::iDrawDirection == Direction::Left)
			{
				Object::iMovingDirection = Direction::Top;
				Object::iDrawDirection = Direction::Right;
				Object::ChangeColor();
			}
			else if (Object::fTrianglePos[2][0] < 0.4f && Object::iMovingDirection == Direction::Bottom && Object::iDrawDirection == Direction::Left)
			{
				Object::iMovingDirection = Direction::Right;
				Object::iDrawDirection = Direction::Right;
				Object::ChangeColor();
			}
			else if (Object::fTrianglePos[2][0] > 1.0f && Object::iMovingDirection == Direction::Right && Object::iDrawDirection == Direction::Right)
			{
				Object::iMovingDirection = Direction::Bottom;
				Object::iDrawDirection = Direction::Left;
				Object::ChangeColor();
			}
		}
	}
	else
	{
		if (Object::fTrianglePos[0][0] < -0.4f && Object::iMovingDirection != Direction::Top)
		{
			Object::iMovingDirection = Direction::Top;
			Object::iDrawDirection = Direction::Right;
			Object::ChangeColor();
		}
		else if (Object::fTrianglePos[0][1] > 0.2f && Object::iMovingDirection != Direction::Right)
		{
			Object::iMovingDirection = Direction::Right;
			Object::iDrawDirection = Direction::Bottom;
			Object::ChangeColor();
		}
		else if (Object::fTrianglePos[0][0] > 0.4f && Object::iMovingDirection != Direction::Bottom)
		{
			Object::iMovingDirection = Direction::Bottom;
			Object::iDrawDirection = Direction::Left;
			Object::ChangeColor();
		}
		else if (Object::fTrianglePos[0][1] < -0.2f && Object::iMovingDirection != Direction::Left)
		{
			Object::iMovingDirection = Direction::Left;
			Object::iDrawDirection = Direction::Top;
			Object::ChangeColor();
		}
	}
}
BOOL Object::StartTimer()
{
	return Object::bStartTimer;
}
GLvoid Object::ChangeTimer(GLint iTruthValue)
{
	Object::bStartTimer = iTruthValue;
}
Object::~Object()
{

}

Object* oOutside[10];
Object* oInside[2];
GLuint uiVAO[VAO_NUM], uiVBO[VBO_NUM];

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;

	if (!bInitialize)
	{
		glGenVertexArrays(VAO_NUM, uiVAO);
		glGenBuffers(VBO_NUM, uiVBO);

		for (GLint i = 0; i < 10; ++i)
		{
			if (i < 2)
				oInside[i] = new Object(i + 1);

			oOutside[i] = new Object(0);
		}

		GLfloat Rect[4][3] =
		{
			{-0.4f, 0.4f, 0.0f},
			{-0.4f, -0.4f, 0.0f},
			{0.4f, -0.4f, 0.0f},
			{0.4f, 0.4f, 0.0f}
		};

		glBindVertexArray(uiVAO[VAO_NUM - 1]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[VBO_NUM - 1]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), Rect, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		bInitialize = TRUE;
	}

	GLfloat Triangle[12][3][3], TriangleColor[12][3][3];

	for (GLint k = 0; k < 12; ++k)
	{
		for (GLint i = 0; i < 3; ++i)
		{
			for (GLint j = 0; j < 3; ++j)
			{
				if (k < 10)
				{
					Triangle[k][i][j] = oOutside[k]->TrianglePos(i, j);
					TriangleColor[k][i][j] = oOutside[k]->Color(i, j);
				}
				else
				{
					Triangle[k][i][j] = oInside[k - 10]->TrianglePos(i, j);
					TriangleColor[k][i][j] = oInside[0]->Color(i, j);
				}
			}
		}
	}

	for (GLint i = 0; i < VAO_NUM - 1; ++i)
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

	glBindVertexArray(uiVAO[VAO_NUM - 1]);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	for (GLint i = 0; i < VAO_NUM - 1; ++i)
	{
		glBindVertexArray(uiVAO[i]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Timer(GLint iValue)
{
	if ((iValue >= 0 && iValue <= 9) && oOutside[iValue]->StartTimer())
	{
		oOutside[iValue]->ChangeDirection(0);
		oOutside[iValue]->ChangePos();
	}
	else if (iValue == 10 && oInside[0]->StartTimer())
	{
		oInside[0]->ChangeDirection(1);
		oInside[0]->ChangePos();
	}
	else if (iValue == 11 && oInside[1]->StartTimer())
	{
		oInside[1]->ChangeDirection(1);
		oInside[1]->ChangePos();
	}

	glutTimerFunc(1, Timer, iValue);
	InitializeBuffer();
	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'S': case 's':
	{
		for (GLint i = 0; i < VAO_NUM - 1; ++i)
		{
			if (i < 2)
				oInside[i]->ChangeTimer(TRUE);

			oOutside[i]->ChangeTimer(TRUE);

			Timer(i);
		}

		break;
	}
	case 'T': case 't':
	{

		for (GLint i = 0; i < VAO_NUM - 1; ++i)
		{
			if (i < 2)
				oInside[i]->ChangeTimer(FALSE);

			oOutside[i]->ChangeTimer(FALSE);
		}
		break;
	}
	case 'Q': case 'q':
	{
		for (GLint i = 0; i < 10; ++i)
		{
			if (i < 2)
				delete oInside[i];

			delete oOutside[i];
		}
		exit(0);
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
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