#include "Shader_4.h"

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
	glutMainLoop();													// 이벤트 처리 시작
}