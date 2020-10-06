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
#define VAO 1
#define VBO 2

typedef struct Position
{
	GLfloat iX, iY, iZ;
} Pos;

//상단 꼭지점의 방향
enum Direction
{
	Top, Right, Bottom, Left
};

class Shader
{
private:
	GLuint uiVertexShader;
	GLuint uiFragmentShader;
	GLuint uiShaderProgramID;
	GLuint uiShaderID;
public:
	Shader();
	GLuint VertexShader();
	GLuint FragmentShader();
	GLuint ShaderProgram();
	GLvoid InputShaderID(GLuint);
	GLuint ShaderID();
	~Shader();
};

Shader::Shader()
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
Shader::~Shader()
{

}

class Object
{
private:
	Pos pTriangleCenter;
	GLfloat fTrianglePos[3][3];
	GLfloat fColor[3][3];
	GLint iDirection;
	BOOL bStartTimer;
public:
	Object();
	GLfloat TrianglePos(GLint, GLint);
	GLvoid ChangePos();
	GLfloat Color(GLint, GLint);
	GLvoid ChangeColor();
	GLint Direction();
	GLvoid ChangeDirection();
	BOOL StartTimer();
	GLvoid ChangeTimer(GLint);
	~Object();
};

Object::Object()
{
	Object::pTriangleCenter.iX = 0.0f;
	Object::pTriangleCenter.iY = -0.8f;
	Object::pTriangleCenter.iZ = 1.0f;
	Object::iDirection = Direction::Top;

	Object::ChangeColor();
	Object::ChangePos();

	Object::bStartTimer = FALSE;
}
GLfloat Object::TrianglePos(GLint i, GLint j)
{
	return Object::fTrianglePos[i][j];
}
GLvoid Object::ChangePos()
{
	switch (Object::iDirection)
	{
	case Direction::Top:
	{
		Object::pTriangleCenter.iX -= 0.005f;
		Object::pTriangleCenter.iY += 0.005f;

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + pow(-1, i + 1) * 0.1f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY - 0.2f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY + 0.3f;

		break;
	}
	case Direction::Right:
	{
		Object::pTriangleCenter.iX += 0.005f;
		Object::pTriangleCenter.iY += 0.005f;

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX - 0.2f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + pow(-1, i + 1) * 0.1f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX + 0.3f;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY;

		break;
	}
	case Direction::Bottom:
	{
		Object::pTriangleCenter.iX += 0.005f;
		Object::pTriangleCenter.iY -= 0.005f;

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + pow(-1, i) * 0.1f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + 0.2f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY - 0.3f;

		break;
	}
	case Direction::Left:
	{
		Object::pTriangleCenter.iX -= 0.005f;
		Object::pTriangleCenter.iY -= 0.005f;

		for (GLint i = 0; i < 2; ++i)
		{
			Object::fTrianglePos[i][0] = Object::pTriangleCenter.iX + 0.2f;
			Object::fTrianglePos[i][1] = Object::pTriangleCenter.iY + pow(-1, i) * 0.1f;
		}

		Object::fTrianglePos[2][0] = Object::pTriangleCenter.iX - 0.3f;
		Object::fTrianglePos[2][1] = Object::pTriangleCenter.iY;

		break;
	}
	default:
		break;
	}
}
GLfloat Object::Color(GLint i, GLint j)
{
	return Object::fColor[i][j];
}
GLvoid Object::ChangeColor()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_real_distribution<GLfloat> uDis(0.0f, 1.0f);

	for (GLint i = 0; i < 3; ++i)
	{
		for (GLint j = 0; j < 3; ++j)
		{
			Object::fColor[i][j] = uDis(mGen);
		}
	}
}
GLvoid Object::ChangeDirection()
{
	if (Object::fTrianglePos[0][0] < -1.0f)
	{
		Object::iDirection = Direction::Right;
		Object::ChangeColor();
	}
	else if (Object::fTrianglePos[0][1] > 0.8f)
	{
		Object::iDirection = Direction::Bottom;
		Object::ChangeColor();
	}
	else if (Object::fTrianglePos[0][0] > 1.0f)
	{
		Object::iDirection = Direction::Left;
		Object::ChangeColor();
	}
	else if (Object::fTrianglePos[0][1] < -0.8f)
	{
		Object::iDirection = Direction::Top;
		Object::ChangeColor();
	}
}
BOOL Object::StartTimer()
{
	return Object::bStartTimer;
}
GLvoid Object::ChangeTimer(GLint iTruthValue)
{
	Object::bStartTimer = iTruthValue;
}
Object::~Object()
{

}

Shader mMaster;
Object oObject;
GLuint uiVAO, uiVBO[VBO];

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

GLvoid InitializeShader()
{
	GLuint ShaderID = MakeShaderProgram();
	mMaster.InputShaderID(ShaderID);
}

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;

	GLfloat Triangle[3][3], TriangleColor[3][3];

	for (GLint i = 0; i < 3; ++i)
	{
		for (GLint j = 0; j < 3; ++j)
		{
			Triangle[i][j] = oObject.TrianglePos(i, j);
			TriangleColor[i][j] = oObject.Color(i, j);
		}
	}

	if (!bInitialize)
	{
		glGenVertexArrays(VAO, &uiVAO);
		glGenBuffers(VBO, uiVBO);

		bInitialize = TRUE;
	}

	glBindVertexArray(uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Triangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TriangleColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// 바탕색을 흰색으로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// 설정된 색으로 전체를 칠하기

	GLuint ShaderID = mMaster.ShaderID();
	glUseProgram(ShaderID);

	glBindVertexArray(uiVAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Timer(GLint iValue)
{
	if (oObject.StartTimer())
	{
		oObject.ChangeDirection();
		oObject.ChangePos();

		InitializeBuffer();
		glutTimerFunc(1, Timer, 1);
	}

	glutPostRedisplay();
}

GLvoid Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	switch (ubKey)
	{
	case 'S': case 's':
	{
		oObject.ChangeTimer(TRUE);
		Timer(1);
		break;
	}
	case 'T': case 't':
	{
		oObject.ChangeTimer(FALSE);
		break;
	}
	case 'Q': case 'q':
	{
		exit(0);
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)							// 콜백 함수 : 다시 그리기 콜백 함수
{
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid FuctionalizeGlut()
{
	glutDisplayFunc(DrawScene);											// 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);											// 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(1, Timer, 1);
	glutMainLoop();														// 이벤트 처리 시작
}