//실습 7번
#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VAO_NUM 10
#define VBO_NUM 20

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
	GLint iMovingDirection;
	BOOL bStartTimer;
public:
	Object();
	GLfloat TrianglePos(GLint, GLint);
	GLvoid ChangePos();
	GLfloat Color(GLint, GLint);
	GLvoid ChangeColor();
	GLvoid ChangeDirection();
	BOOL StartTimer();
	GLvoid ChangeTimer(GLint);
	~Object();
};

Object::Object()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uRealDis(-1.0f, 1.0f);
	std::uniform_int_distribution<GLint> uIntDis(Top, Left);

	Object::pTriangleCenter.iX = uRealDis(mGen);
	Object::pTriangleCenter.iY = uRealDis(mGen);
	Object::pTriangleCenter.iZ = 1.0f;
	Object::iMovingDirection = uIntDis(mGen);

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
	case Direction::Top:
	{
		Object::pTriangleCenter.iX -= 0.01f;
		Object::pTriangleCenter.iY += 0.01f;

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + pow(-1, i + 1) * 0.1f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY - 0.2f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY + 0.3f;

		break;
	}
	case Direction::Right:
	{
		Object::pTriangleCenter.iX += 0.01f;
		Object::pTriangleCenter.iY += 0.01f;

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX - 0.2f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + pow(-1, i + 1) * 0.1f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX + 0.3f;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY;

		break;
	}
	case Direction::Bottom:
	{
		Object::pTriangleCenter.iX += 0.01f;
		Object::pTriangleCenter.iY -= 0.01f;

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + pow(-1, i) * 0.1f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + 0.2f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY - 0.3f;

		break;
	}
	case Direction::Left:
	{
		Object::pTriangleCenter.iX -= 0.01f;
		Object::pTriangleCenter.iY -= 0.01f;

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + 0.2f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + pow(-1, i) * 0.1f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX - 0.3f;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY;

		break;
	}
	default:
		break;
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
GLvoid Object::ChangeDirection()
{
	if (Object::fTrianglePos[0][0] < -1.0f && Object::iMovingDirection != Direction::Right)
	{
		Object::iMovingDirection = Direction::Right;
		Object::ChangeColor();
	}
	else if (Object::fTrianglePos[0][1] > 0.8f && Object::iMovingDirection != Direction::Bottom)
	{
		Object::iMovingDirection = Direction::Bottom;
		Object::ChangeColor();
	}
	else if (Object::fTrianglePos[0][0] > 1.0f && Object::iMovingDirection != Direction::Left)
	{
		Object::iMovingDirection = Direction::Left;
		Object::ChangeColor();
	}
	else if (Object::fTrianglePos[0][1] < -0.8f && Object::iMovingDirection != Direction::Top)
	{
		Object::iMovingDirection = Direction::Top;
		Object::ChangeColor();
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

Object oOutside[VAO_NUM];
GLuint uiVAO[VAO_NUM], uiVBO[VBO_NUM];

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;

	GLfloat Triangle[10][3][3], TriangleColor[10][3][3];

	for (GLint k = 0; k < VAO_NUM; ++k)
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
		glGenVertexArrays(VAO_NUM, uiVAO);
		glGenBuffers(VBO_NUM, uiVBO);

		bInitialize = TRUE;
	}

	for (GLint i = 0; i < VAO_NUM; ++i)
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

	for (GLint i = 0; i < VAO_NUM; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Timer(GLint iValue)
{
	if (oOutside[iValue].StartTimer())
	{
		oOutside[iValue].ChangeDirection();
		oOutside[iValue].ChangePos();

		InitializeBuffer();
		glutTimerFunc(1, Timer, iValue);
	}

	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'S': case 's':
	{
		for (GLint i = 0; i < VAO_NUM; ++i)
		{
			oOutside[i].ChangeTimer(TRUE);
			Timer(i);
		}

		break;
	}
	case 'T': case 't':
	{
		for (GLint i = 0; i < VAO_NUM; ++i)
		{
			oOutside[i].ChangeTimer(FALSE);
		}

		break;
	}
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