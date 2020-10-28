#pragma once
#include "Shader3D.h"

enum TimerNum
{
	None, Rotate, Move
};

Shader3D sMaster;
GLint iType = 2;
GLint iDepth = 0;
GLint iPolygon = 0;
GLint iRotate = 0;
GLint iMove = 0;
BOOL iReset = GL_FALSE;
Pos Coord = { 0.0f, 0.0f, 0.0f };
Angle Degree = { 0.0f, 0.0f, 0.0f };
glm::vec3 Translate(0.0f, 0.0f, 0.0f);

GLvoid Timer(GLint iValue)
{
	switch (iMove)
	{
	case 1:
	{
		Translate = { 0.01f, 0.0f, 0.0f };

		break;
	}
	case 2:
	{
		Translate = { -0.01f, 0.0f, 0.0f };

		break;
	}
	case 3:
	{
		Translate = { 0.0f, 0.01f, 0.0f };

		break;
	}
	case 4:
	{
		Translate = { 0.0f, -0.01f, 0.0f };

		break;
	}
	default:
		Translate = { 0.0f, 0.0f, 0.0f };

		break;
	}

	switch (iRotate)
	{
	case 1:
	{
		Degree.fX = 1.0f;

		break;
	}
	case 2:
	{
		Degree.fX = -1.0f;

		break;
	}
	case 3:
	{
		Degree.fY = 1.0f;

		break;
	}
	case 4:
	{
		Degree.fY = -1.0f;

		break;
	}
	default:
		Degree.fX = 0.0f;
		Degree.fY = 0.0f;

		break;
	}

	if (!iReset)
	{
		sMaster.Reset(GL_FALSE);
		sMaster.InputTranslateCoordinate(Translate);
		sMaster.InputRotationFactor(Degree);
	}
	else
	{
		sMaster.Reset(GL_TRUE);
	}

	sMaster.TranslateShader(GL_TRUE);
	sMaster.RotateShader(GL_TRUE);

	sMaster.InitializeBuffer();
	glutTimerFunc(1, Timer, 1);
	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'C': case 'c':
	{
		iType = 1;
		break;
	}
	case 'P': case 'p':
	{
		iType = 2;
		break;
	}
	case 'H': case 'h':
	{
		++iDepth;

		break;
	}
	case 'x':
	{
		iReset = GL_FALSE;
		iRotate = 1;
		glutTimerFunc(1, Timer, 1);

		break;
	}
	case 'X':
	{
		iReset = GL_FALSE;
		iRotate = 2;
		glutTimerFunc(1, Timer, 1);

		break;
	}
	case 'y':
	{
		iReset = GL_FALSE;
		iRotate = 3;
		glutTimerFunc(1, Timer, 1);

		break;
	}
	case 'Y':
	{
		iReset = GL_FALSE;
		iRotate = 4;
		glutTimerFunc(1, Timer, 1);

		break;
	}
	case 'W': case 'w':
	{
		++iPolygon;

		break;
	}
	case 'S': case 's':
	{
		iRotate = 0;
		iMove = 0;
		iReset = GL_TRUE;
		glutTimerFunc(1, Timer, 1);

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

GLvoid Special(GLint ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case GLUT_KEY_LEFT:
	{
		iReset = GL_FALSE;
		iMove = 2;
		glutTimerFunc(1, Timer, 1);

		break;
	}
	case GLUT_KEY_RIGHT:
	{
		iReset = GL_FALSE;
		iMove = 1;
		glutTimerFunc(1, Timer, 1);

		break;
	}
	case GLUT_KEY_UP:
	{
		iReset = GL_FALSE;
		iMove = 3;
		glutTimerFunc(1, Timer, 1);

		break;
	}
	case GLUT_KEY_DOWN:
	{
		iReset = GL_FALSE;
		iMove = 4;
		glutTimerFunc(1, Timer, 1);

		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid SpecialUp(GLint ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case GLUT_KEY_LEFT: case GLUT_KEY_RIGHT: case GLUT_KEY_UP: case GLUT_KEY_DOWN:
	{
		iMove = 0;

		break;
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

	if (iDepth % 2 == 0)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	if (iPolygon % 2 == 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	sMaster.DrawPolygon(Coord, iType);

	glutSwapBuffers();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)
{
	glViewport(0, 0, iWidth, iHeight);
}