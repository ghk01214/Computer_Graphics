#include "Shader_4.h"

void main(GLint iArgc, CHAR** cArgv)									//������ ����ϰ� �ݹ��Լ� ����
{
	//������ �����ϱ�
	glutInit(&iArgc, cArgv);											// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);									// �������� ��ġ ����
	glutInitWindowSize(800, 600);									// �������� ũ�� ����
	glutCreateWindow("Excercise 1");								// ������ ���� ������ �̸�

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)										// glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized n";

	glutDisplayFunc(DrawScene);										// ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape);										// �ٽ� �׸��� �ݹ��Լ� ����
	glutMainLoop();													// �̺�Ʈ ó�� ����
}