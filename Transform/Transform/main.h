#pragma once
#include "Shader3D.h"

Shader3D sMaster;
GLint iDepth = 0;
GLint iPolygon = 0;
BOOL bTimer = FALSE;
Angle Degree = {0.0f, 0.0f, 0.0f};

GLvoid Timer(GLint iValue)
{
	if (bTimer)
	{
		switch (iValue)
		{
		case 1:
		{
			if (Degree.fX > 360.0f)
			{
				Degree.fX = 0.0f;
			}
			else
			{
				Degree.fX = 1.0f;
			}

			sMaster.ChangeRotation(FALSE);
			sMaster.InputRotationFactor(Degree);
			break;
		}
		case 2:
		{

		}
		default:
			break;
		}

		sMaster.InitializeBuffer();

		glutTimerFunc(100, Timer, iValue);
		glutPostRedisplay();
	}
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'C': case 'c':
	{

		break;
	}
	case 'P': case 'p':
	{

		break;
	}
	case 'H': case 'h':
	{
		++iDepth;

		break;
	}
	case 'x':
	{
		bTimer = TRUE;
		glutTimerFunc(100, Timer, 1);
		//Timer(1);
		break;
	}
	case 'X':
	{
		glutTimerFunc(1, Timer, 2);
		break;
	}
	case 'y':
	{

		break;
	}
	case 'Y':
	{

		break;
	}
	case 'W': case 'w':
	{
		++iPolygon;

		break;
	}
	case GLUT_KEY_LEFT:
	{


		break;
	}
	case GLUT_KEY_RIGHT:
	{


		break;
	}
	case GLUT_KEY_UP:
	{


		break;
	}
	case GLUT_KEY_DOWN:
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

GLvoid KeyUp(GLubyte ubKey, GLint iX, GLint iY)
{

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

	sMaster.DrawPolygon(0.0f, 0.0f, 0.0f, 2);

	glutSwapBuffers();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)
{
	glViewport(0, 0, iWidth, iHeight);
}