#include "header.h"
#include "define.h"
#include "main.h"

GLvoid main(GLint iArgc, GLchar** cArgv)
{
	//������ �����ϱ�
	glutInit(&iArgc, cArgv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(NUM::WINDOW_POS, NUM::WINDOW_POS);
	glutInitWindowSize(NUM::WINDOW_WIDTH, NUM::WINDOW_HEIGHT);
	glutCreateWindow("openGL");

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized n";

	CallBackFunc();
	glutMainLoop();
}