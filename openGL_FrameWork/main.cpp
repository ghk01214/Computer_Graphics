#include "header.h"
#include "define.h"
#include "ShaderAdmin.h"

ShaderAdmin sAdmin;

GLvoid DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sAdmin.MakeShader(Manage::Triangle);

	glutSwapBuffers();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)
{
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid main(GLint iArgc, GLchar** cArgv)
{
	//윈도우 생성하기
	glutInit(&iArgc, cArgv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(NUM::WINDOW_POS, NUM::WINDOW_POS);
	glutInitWindowSize(NUM::WINDOW_WIDTH, NUM::WINDOW_HEIGHT);
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

	sAdmin.MakeShader(Manage::Triangle);

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	//glutKeyboardFunc(Keyboard);
	//glutSpecialFunc(Special);
	//glutSpecialUpFunc(SpecialUp);
	glutMainLoop();
}