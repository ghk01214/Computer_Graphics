#include <iostream>
#include <random>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLvoid DrawScene(GLvoid);
GLvoid Reshape(GLint, GLint);
GLvoid Mouse(GLint, GLint, GLint, GLint);
GLvoid Keyboard(GLubyte, GLint, GLint);
GLvoid Timer(GLint);

std::random_device rRandom;
std::mt19937 mGen(rRandom());
std::uniform_int_distribution<GLint> uDis(0.0f, 1.0f);

GLfloat r = uDis(mGen);
GLfloat g = uDis(mGen);
GLfloat b = uDis(mGen);

GLfloat x = 0;
GLfloat y = 0;
GLfloat d = 0;
bool bStopTimer = TRUE;
bool bUp = TRUE;

void main(GLint iArgc, CHAR** cArgv)									//������ ����ϰ� �ݹ��Լ� ����
{
	//������ �����ϱ�
	glutInit(&iArgc, cArgv);										// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);									// �������� ��ġ ����
	glutInitWindowSize(800, 800);									// �������� ũ�� ����
	glutCreateWindow("Excercise 3");								// ������ ���� ������ �̸�

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)										// glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized n";

	glutDisplayFunc(DrawScene);										// ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape);										// �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard);										// Ű���� �Է� �ݹ��Լ� ����
	glutMouseFunc(Mouse);											// ���콺 �Է� �ݹ��Լ� ����
	glutTimerFunc(1, Timer, 1);									// Ÿ�̸� �ݹ��Լ� ����
	glutMainLoop();													// �̺�Ʈ ó�� ����
}

GLvoid DrawScene()													// �ݹ� �Լ� : �׸��� �ݹ� �Լ�
{
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);						// �������� ���������� ����
	glClear(GL_COLOR_BUFFER_BIT);									// ������ ������ ��ü�� ĥ�ϱ�

	glColor3f(r, g, b);												// �簢�� ������ ���������� ����
	glRectf(x - 0.3, y + d - 0.3, x + 0.3, y + d + 0.3);				// �簢���� ���콺�� Ŭ�� ������ �߽����� �ϴ� �� ���� ���̰� 0.6�� ���簢���� �׸���

	//�׸��� �κ� ����
	//�׸��� ���� �κ��� ���⿡ ���Եȴ�
	glutSwapBuffers();												// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(GLint iWidth, GLint iHeight)								// �ݹ� �Լ� : �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	if (iButton == GLUT_LEFT_BUTTON && iState == GLUT_DOWN)
	{
		x = (GLfloat)(iX - 400) / 400;
		y = (GLfloat)(400 - iY) / 400;

		r = uDis(mGen);
		g = uDis(mGen);
		b = uDis(mGen);
	}

	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'A': case 'a':
	{
		bStopTimer = FALSE;
		Timer(1);
		break;
	}
	case 'S': case 's':
	{
		bStopTimer = TRUE;
		break;
	}
	case 'Q': case 'q':
	{
		glutDestroyWindow(1);
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid Timer(GLint iValue)
{
	glutPostRedisplay();												// DrawScene �Լ� ȣ��

	if (!bStopTimer)
	{
		if (d > 0.1)
			bUp = FALSE;
		else if (d < -0.1)
			bUp = TRUE;

		if (bUp)
			d += 0.01;
		else
			d -= 0.01;

		glutTimerFunc(1, Timer, 1);									// Ÿ�̸� �ݹ��Լ� ����
	}
}
