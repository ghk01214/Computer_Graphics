#include "header.h"
#include "define.h"
#include "main.h"

GLvoid main(GLint iArgc, GLchar** cArgv)
{
	//������ �����ϱ�
	glutInit(&iArgc, cArgv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(Num::WINDOW_POS, Num::WINDOW_POS);
	glutInitWindowSize(Num::WINDOW_WIDTH, Num::WINDOW_HEIGHT);
	glutCreateWindow("openGL");

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;

	CallBackFunc();
	glutMainLoop();
}