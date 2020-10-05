//실습 7번
#include "Shader_4.h"

GLvoid main(GLint iArgc, CHAR** cArgv)									//윈도우 출력하고 콜백함수 설정
{
	//윈도우 생성하기
	glutInit(&iArgc, cArgv);											// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);						// 디스플레이 모드 설정
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);					// 윈도우의 위치 지정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);					// 윈도우의 크기 지정
	glutCreateWindow("Shader 4");										// 윈도우 생성 윈도우 이름

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)											// glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized n";

	InitializeBuffer();
	InitializeShader();
	FuctionalizeGlut();
}