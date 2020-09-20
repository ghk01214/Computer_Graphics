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
GLvoid Keyboard(GLubyte, GLint, GLint);
GLvoid Timer(GLint);
void RandomColor();
bool bKeyDown = FALSE;
bool bStopTimer = TRUE;

void main(GLint iArgc, CHAR** cArgv)									//������ ����ϰ� �ݹ��Լ� ����
{
	//������ �����ϱ�
	glutInit(&iArgc, cArgv);											// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);									// �������� ��ġ ����
	glutInitWindowSize(800, 600);									// �������� ũ�� ����
	glutCreateWindow("Excercise 1");								// ������ ���� ������ �̸�

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
	glutTimerFunc(1000, Timer, 1);									// Ÿ�̸� �ݹ��Լ� ����
	glutMainLoop();													// �̺�Ʈ ó�� ����
}

GLvoid DrawScene()													// �ݹ� �Լ� : �׸��� �ݹ� �Լ�
{
	if (!bKeyDown)
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);						// �������� ������� ����

	glClear(GL_COLOR_BUFFER_BIT);									// ������ ������ ��ü�� ĥ�ϱ�

	//�׸��� �κ� ����
	//�׸��� ���� �κ��� ���⿡ ���Եȴ�
	glutSwapBuffers();												// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(GLint iWidth, GLint iHeight)										// �ݹ� �Լ� : �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'R': case 'r':
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);							// �������� ���������� ����
		break;
	}
	case 'G': case 'g':
	{
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);							// �������� �ʷϻ����� ����
		break;
	}
	case 'B': case 'b':
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);							// �������� �Ķ������� ����
		break;
	}
	case 'A': case 'a':
	{
		RandomColor();
		break;
	}
	case 'W': case 'w':
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// �������� ������� ����
		break;
	}
	case 'K': case 'k':
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);							// �������� ���������� ����
		break;
	}
	case 'T': case 't':
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

	bKeyDown = TRUE;
	glutPostRedisplay();												// DrawScene �Լ� ȣ��
}

GLvoid Timer(GLint iValue)
{
	RandomColor();
	glutPostRedisplay();												// DrawScene �Լ� ȣ��
	if (!bStopTimer)
		glutTimerFunc(1000, Timer, 1);									// Ÿ�̸� �ݹ��Լ� ����
}

void RandomColor()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<GLint> uDis(0.0f, 1.0f);

	GLfloat r = uDis(mGen);
	GLfloat g = uDis(mGen);
	GLfloat b = uDis(mGen);

	glClearColor(r, g, b, 1.0f);									// �������� ���������� ����
}