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

std::random_device rRandom;
std::mt19937 mGen(rRandom());
std::uniform_int_distribution<GLint> uDis(0.0f, 1.0f);

GLfloat r1 = uDis(mGen);
GLfloat g1 = uDis(mGen);
GLfloat b1 = uDis(mGen);

GLfloat r2 = uDis(mGen);
GLfloat g2 = uDis(mGen);
GLfloat b2 = uDis(mGen);

void main(GLint iArgc, CHAR** cArgv)									//������ ����ϰ� �ݹ��Լ� ����
{
	//������ �����ϱ�
	glutInit(&iArgc, cArgv);											// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);									// �������� ��ġ ����
	glutInitWindowSize(800, 800);									// �������� ũ�� ����
	glutCreateWindow("Excercise 2");								// ������ ���� ������ �̸�

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
	glutMouseFunc(Mouse);											// ���콺 �Է� �ݹ��Լ� ����
	glutMainLoop();													// �̺�Ʈ ó�� ����
}

GLvoid DrawScene()													// �ݹ� �Լ� : �׸��� �ݹ� �Լ�
{
	glClearColor(r1, g1, b1, 1.0f);									// �������� ���������� ����
	glClear(GL_COLOR_BUFFER_BIT);									// ������ ������ ��ü�� ĥ�ϱ�

	glColor3f(r2, g2, b2);											// �簢�� ������ ���������� ����
	glRectf(-0.5, -0.5, 0.5, 0.5);									// �簢���� (-0.5, -0.5), (0.5, 0.5) ���̿� �׸���

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
		if ((iX >= 200 && iX <= 600) && (iY >= 200 && iY <= 600))	// �簢�� ���θ� Ŭ��
		{
			r2 = uDis(mGen);
			g2 = uDis(mGen);
			b2 = uDis(mGen);
		}
		else														// �簢�� �ܺθ� Ŭ��
		{
			r1 = uDis(mGen);
			g1 = uDis(mGen);
			b1 = uDis(mGen);
		}
	}
}