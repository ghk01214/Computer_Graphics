#include <iostream>
#include <random>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
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