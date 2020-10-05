//�ǽ� 7��
#include "Shader_4.h"

GLvoid main(GLint iArgc, CHAR** cArgv)									//������ ����ϰ� �ݹ��Լ� ����
{
	//������ �����ϱ�
	glutInit(&iArgc, cArgv);											// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);						// ���÷��� ��� ����
	glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);					// �������� ��ġ ����
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);					// �������� ũ�� ����
	glutCreateWindow("Shader 4");										// ������ ���� ������ �̸�

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)											// glew �ʱ�ȭ
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