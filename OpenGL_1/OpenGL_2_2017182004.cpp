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

void main(GLint iArgc, CHAR** cArgv)									//윈도우 출력하고 콜백함수 설정
{
	//윈도우 생성하기
	glutInit(&iArgc, cArgv);											// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);									// 윈도우의 위치 지정
	glutInitWindowSize(800, 800);									// 윈도우의 크기 지정
	glutCreateWindow("Excercise 2");								// 윈도우 생성 윈도우 이름

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
	glutMouseFunc(Mouse);											// 마우스 입력 콜백함수 지정
	glutMainLoop();													// 이벤트 처리 시작
}

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
	glClearColor(r1, g1, b1, 1.0f);									// 바탕색을 랜덤색으로 지정
	glClear(GL_COLOR_BUFFER_BIT);									// 설정된 색으로 전체를 칠하기

	glColor3f(r2, g2, b2);											// 사각형 색상을 랜덤색으로 지정
	glRectf(-0.5, -0.5, 0.5, 0.5);									// 사각형을 (-0.5, -0.5), (0.5, 0.5) 사이에 그린다

	//그리기 부분 구현
	//그리기 관련 부분이 여기에 포함된다
	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Reshape(GLint iWidth, GLint iHeight)								// 콜백 함수 : 다시 그리기 콜백 함수
{
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	if (iButton == GLUT_LEFT_BUTTON && iState == GLUT_DOWN)
	{
		if ((iX >= 200 && iX <= 600) && (iY >= 200 && iY <= 600))	// 사각형 내부를 클릭
		{
			r2 = uDis(mGen);
			g2 = uDis(mGen);
			b2 = uDis(mGen);
		}
		else														// 사각형 외부를 클릭
		{
			r1 = uDis(mGen);
			g1 = uDis(mGen);
			b1 = uDis(mGen);
		}
	}
}