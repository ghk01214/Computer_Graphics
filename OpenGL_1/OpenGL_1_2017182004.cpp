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

void main(GLint iArgc, CHAR** cArgv)									//윈도우 출력하고 콜백함수 설정
{
	//윈도우 생성하기
	glutInit(&iArgc, cArgv);											// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);									// 윈도우의 위치 지정
	glutInitWindowSize(800, 600);									// 윈도우의 크기 지정
	glutCreateWindow("Excercise 1");								// 윈도우 생성 윈도우 이름

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)										// glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized n";

	glutDisplayFunc(DrawScene);										// 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);										// 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard);										// 키보드 입력 콜백함수 지정
	glutTimerFunc(1000, Timer, 1);									// 타이머 콜백함수 설정
	glutMainLoop();													// 이벤트 처리 시작
}

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
	if (!bKeyDown)
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);						// 바탕색을 흰색으로 지정

	glClear(GL_COLOR_BUFFER_BIT);									// 설정된 색으로 전체를 칠하기

	//그리기 부분 구현
	//그리기 관련 부분이 여기에 포함된다
	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Reshape(GLint iWidth, GLint iHeight)										// 콜백 함수 : 다시 그리기 콜백 함수
{
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'R': case 'r':
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);							// 바탕색을 빨강색으로 지정
		break;
	}
	case 'G': case 'g':
	{
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);							// 바탕색을 초록색으로 지정
		break;
	}
	case 'B': case 'b':
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);							// 바탕색을 파랑색으로 지정
		break;
	}
	case 'A': case 'a':
	{
		RandomColor();
		break;
	}
	case 'W': case 'w':
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// 바탕색을 흰색으로 지정
		break;
	}
	case 'K': case 'k':
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);							// 바탕색을 검정색으로 지정
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
	glutPostRedisplay();												// DrawScene 함수 호출
}

GLvoid Timer(GLint iValue)
{
	RandomColor();
	glutPostRedisplay();												// DrawScene 함수 호출
	if (!bStopTimer)
		glutTimerFunc(1000, Timer, 1);									// 타이머 콜백함수 설정
}

void RandomColor()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<GLint> uDis(0.0f, 1.0f);

	GLfloat r = uDis(mGen);
	GLfloat g = uDis(mGen);
	GLfloat b = uDis(mGen);

	glClearColor(r, g, b, 1.0f);									// 바탕색을 랜덤색으로 지정
}