#include "Shader.h"
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct Position
{
	GLfloat iX, iY;
} Pos;

typedef struct Color
{
	GLfloat fR, fG, fB;
} Col;

enum Crash
{
	None, Left, Right, Top, Bottom
};

GLuint uiVAO[4], uiVBO[8];
BOOL bChangeColor = FALSE;
BOOL bStartTimer = FALSE;
GLint iCrash[4] =
{
	Right, Right, Right, Right
};

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
GLfloat cfColor[4][3][3] =
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
	glutDisplayFunc(DrawScene);											// ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape);											// �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(1, Timer, 1);												// �̺�Ʈ ó�� ����
	glutMainLoop();														// �̺�Ʈ ó�� ����
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
	cfTriangle[i][0][0] = pTrianglePos[i].iX - 0.2;
	cfTriangle[i][0][1] = pTrianglePos[i].iY - 0.2;

	cfTriangle[i][1][0] = pTrianglePos[i].iX + 0.2;
	cfTriangle[i][1][1] = pTrianglePos[i].iY - 0.2;

	cfTriangle[i][2][0] = pTrianglePos[i].iX;
	cfTriangle[i][2][1] = pTrianglePos[i].iY + 0.2;
}

GLvoid DrawScene()													// �ݹ� �Լ� : �׸��� �ݹ� �Լ�
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// �������� ������� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// ������ ������ ��ü�� ĥ�ϱ�

	GLuint ShaderID = mMaster.ShaderID();
	glUseProgram(ShaderID);

	if (bChangeColor)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int i = 0; i < 4; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glutSwapBuffers();												// ȭ�鿡 ����ϱ�
}

GLvoid Timer(GLint iValue)
{
	if (bStartTimer)
	{
		for (GLint i = 0; i < 4; ++i)
		{
			if (cfTriangle[i][1][0] > 1.0)
			{
				pTrianglePos[i].iX = 0.8;
				iCrash[i] = Top;
			}
			else if (cfTriangle[i][2][1] > 1.0)
			{
				pTrianglePos[i].iY = 0.8;
				iCrash[i] = Left;
			}
			else if (cfTriangle[i][0][0] < -1.0)
			{
				pTrianglePos[i].iX = -0.8;
				iCrash[i] = Bottom;
			}
			else if (cfTriangle[i][0][1] < -1.0)
			{
				pTrianglePos[i].iY = -0.8;
				iCrash[i] = Right;
			}
		}

		for (GLint i = 0; i < 4; ++i)
		{
			switch (iCrash[i])
			{
			case Top:
			{
				pTrianglePos[i].iY += 0.05;
				break;
			}
			case Bottom:
			{
				pTrianglePos[i].iY -= 0.03;
				break;
			}
			case Left:
			{
				pTrianglePos[i].iX -= 0.02;
				break;
			}
			case Right:
			{
				pTrianglePos[i].iX += 0.1;
				break;
			}
			default:
				break;
			}

			ChangePos(i);
		}
		
		InitializeBuffer();
		glutTimerFunc(1, Timer, 1);
	}

	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'F': case 'f':
	{
		if (bChangeColor)
			bChangeColor = FALSE;
		else
			bChangeColor = TRUE;

		break;
	}
	case 'M': case 'm':
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
	case 'C': case 'c':
	{
		std::random_device rRandom;
		std::mt19937 mGen(rRandom());
		std::uniform_real_distribution<GLfloat> uDis(0.0, 1.0);

		for (GLint i = 0; i < 4; ++i)
		{
			for (GLint j = 0; j < 3; ++j)
			{
				for (GLint k = 0; k < 3; ++k)
				{
					cfColor[i][j][k] = uDis(mGen);
				}
			}
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

	InitializeBuffer();
	glutPostRedisplay();
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

GLvoid Reshape(GLint iWidth, GLint iHeight)							// �ݹ� �Լ� : �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, iWidth, iHeight);
}