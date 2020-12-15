// openGL_FrameWork.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "openGL_FrameWork.h"

GLvoid main(GLint iArgc, GLchar** cArgv)
{
	//윈도우 생성하기
	glutInit(&iArgc, cArgv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(800, 600);
	glutCreateWindow("openGL");

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;

	CallBackFunc();

	frame.MakeShader();
	glutMainLoop();
}