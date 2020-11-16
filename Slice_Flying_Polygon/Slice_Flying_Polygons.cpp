#include "header.h"
#include "define.h"
#include "Slice_Flying_Polygons.h"

GLvoid main(GLint iArgc, GLchar** cArgv)
{
	//윈도우 생성하기
	glutInit(&iArgc, cArgv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(Num::WINDOW_POS, Num::WINDOW_POS);
	glutInitWindowSize(Num::WINDOW_WIDTH, Num::WINDOW_HEIGHT);
	glutCreateWindow("Slice Flying Polygon");

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
	glutMainLoop();
}