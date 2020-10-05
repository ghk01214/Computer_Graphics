#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <cmath>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define WINDOW_POS_X 500
#define WINDOW_POS_Y 500
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class Shader
{
private:
	GLuint uiVertexShader;
	GLuint uiFragmentShader;
	GLuint uiShaderProgramID;
	GLuint uiShaderID;
	BOOL bStartTimer;
public:
	Shader();
	GLuint VertexShader();
	GLuint FragmentShader();
	GLuint ShaderProgram();
	GLvoid InputShaderID(GLuint);
	GLuint ShaderID();
	GLvoid ChangeTimer(GLint);
	BOOL StartTimer();
	~Shader();
};

Shader::Shader()
{
	Shader::bStartTimer = FALSE;

	glGenVertexArrays(4, uiVAO);
	glGenBuffers(8, uiVBO);
}
Shader::~Shader()
{

}
GLuint Shader::VertexShader()
{
	return Shader::uiVertexShader;
}
GLuint Shader::FragmentShader()
{
	return Shader::uiFragmentShader;
}
GLuint Shader::ShaderProgram()
{
	return Shader::uiShaderProgramID;
}
GLvoid Shader::InputShaderID(GLuint ShaderID)
{
	Shader::uiShaderID = ShaderID;
}
GLuint Shader::ShaderID()
{
	return Shader::uiShaderID;
}
GLvoid Shader::ChangeTimer(GLint iTruthValue)
{
	Shader::bStartTimer = iTruthValue;
}
BOOL Shader::StartTimer()
{
	return Shader::bStartTimer;
}

Shader mMaster;
GLuint uiVAO[10], uiVBO[10];

GLvoid FuctionalizeGlut()
{
	glutDisplayFunc(DrawScene);											// 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);											// 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(1, Timer, 1);
	glutMainLoop();														// 이벤트 처리 시작
}

GLchar* FileToBuf(const GLchar* cFile)
{
	FILE* fFile;
	GLulong ulLength;
	GLchar* cBuf;

	fFile = fopen(cFile, "rb");

	if (!fFile)
		return NULL;

	fseek(fFile, 0, SEEK_END);
	ulLength = ftell(fFile);
	cBuf = (GLchar*)malloc(ulLength + 1);
	fseek(fFile, 0, SEEK_SET);
	fread(cBuf, ulLength, 1, fFile);
	fclose(fFile);
	cBuf[ulLength] = 0;

	return cBuf;

	//std::string sShaderCode;
	//std::ifstream ifShaderStream(cFile, std::ios::in);

	//if (ifShaderStream.is_open())
	//{
	//	std::stringstream sstr;
	//	sstr << ifShaderStream.rdbuf();
	//	sShaderCode = sstr.str();
	//	ifShaderStream.close();
	//}
}

GLuint MakeVertexShader()
{
	GLchar* cVertexShaderSource = FileToBuf("Vertex_Shader_1.glsl");
	GLuint VertexShader = mMaster.VertexShader();
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &cVertexShaderSource, NULL);
	glCompileShader(VertexShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Vertex Shader Compile Failed\n" << cErrorLog << std::endl;

		return FALSE;
	}

	return VertexShader;
}

GLuint MakeFragmentShader()
{
	GLchar* cFragmentShaderSource = FileToBuf("Fragment_Shader_1.glsl");
	GLuint FragmentShader = mMaster.FragmentShader();
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &cFragmentShaderSource, NULL);
	glCompileShader(FragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Fragment Shader Compile Failed\n" << cErrorLog << std::endl;

		return FALSE;
	}

	return FragmentShader;
}

GLuint MakeShaderProgram()
{
	GLuint VertexShader = MakeVertexShader();;
	GLuint FragmentShader = MakeFragmentShader();;
	GLuint ShaderProgramID = mMaster.ShaderProgram();

	ShaderProgramID = glCreateProgram();
	glAttachShader(ShaderProgramID, VertexShader);
	glAttachShader(ShaderProgramID, FragmentShader);
	glLinkProgram(ShaderProgramID);

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &iResult);

	if (!iResult)
	{
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Shader Program Link Failed\n" << cErrorLog << std::endl;

		return FALSE;
	}

	glUseProgram(ShaderProgramID);

	return ShaderProgramID;
}

GLvoid InitializeBuffer()
{
	for (GLint i = 0; i < 4; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfTriangle[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO[i * 2 + 1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfColor[i], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}

GLvoid InitializeShader()
{
	GLuint ShaderID = MakeShaderProgram();
	mMaster.InputShaderID(ShaderID);
}

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// 바탕색을 흰색으로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// 설정된 색으로 전체를 칠하기

	GLuint ShaderID = mMaster.ShaderID();
	glUseProgram(ShaderID);

	for (int i = 0; i < 4; ++i)
	{
		glBindVertexArray(uiVAO[i]);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Timer(GLint iValue)
{
	if (mMaster.StartTimer())
	{

		InitializeBuffer();
		glutTimerFunc(1, Timer, 1);
	}

	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case '1': case VK_NUMPAD1:
	{

		break;
	}
	case '2': case VK_NUMPAD2:
	{

		break;
	}
	case '3': case VK_NUMPAD3:
	{

		break;
	}
	case 'Q': case 'q':
	{
		glutDestroyWindow(1);
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	static GLint i = 0;

	if (iButton == GLUT_LEFT_BUTTON && iState == GLUT_DOWN)
	{

	}

	InitializeBuffer();
	glutPostRedisplay();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)							// 콜백 함수 : 다시 그리기 콜백 함수
{
	glViewport(0, 0, iWidth, iHeight);
}