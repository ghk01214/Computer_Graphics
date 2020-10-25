#pragma once
#include "Shader3D.h"

Shader3D sMaster;

GLvoid Timer(GLint iValue)
{

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
		static BOOL bDepth = GL_FALSE;

		if (!bDepth)
		{
			glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
			bDepth = GL_TRUE;
		}
		else
		{
			glDisable(GL_DEPTH_TEST | GL_CULL_FACE);
			bDepth = GL_FALSE;
		}

		break;
	}
	case 'x':
	{

		break;
	}
	case 'X':
	{

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
		static BOOL bPolygon = GL_FALSE;

		if (!bPolygon)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			bPolygon = GL_TRUE;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			bPolygon = GL_FALSE;
		}

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

	sMaster.DrawPolygon(0.0f, 0.0f, 0.0f, 1);

	glutSwapBuffers();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)
{
	glViewport(0, 0, iWidth, iHeight);
}