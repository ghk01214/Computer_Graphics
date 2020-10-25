#include "main.h"

GLvoid main(GLint iArgc, GLchar** cArgv)
{
	//윈도우 생성하기
	glutInit(&iArgc, cArgv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("openGL");

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized n";

	sMaster.MakeShaderProgram();
	sMaster.InitializeBuffer();

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(1, Timer, 1);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyUp);
	glutMainLoop();
}