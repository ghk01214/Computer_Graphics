#include <iostream>
#include <string>
#include <fstream>
#include <random>
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

typedef struct Position
{
	GLfloat iX, iY;
} Pos;

GLuint uiVertexShader;
GLuint uiFragmentShader;
GLuint uiShaderProgramID;
GLuint uiShaderID;
GLuint uiVAO[4], uiVBO[8];
Pos pTrianglePos[4] =
{
	{0.5, 0.5},
	{-0.5, 0.5},
	{-0.5, -0.5},
	{0.5, -0.5}
};
GLfloat cfTriangle1[3][3] =
{
	{pTrianglePos[0].iX - 0.2, pTrianglePos[0].iY - 0.2, 0.0},
	{pTrianglePos[0].iX + 0.2, pTrianglePos[0].iY - 0.2, 0.0},
	{pTrianglePos[0].iX, pTrianglePos[0].iY + 0.2, 0.0},
};
GLfloat cfTriangle2[3][3] =
{
	{pTrianglePos[1].iX - 0.2, pTrianglePos[1].iY - 0.2, 0.0},
	{pTrianglePos[1].iX + 0.2, pTrianglePos[1].iY - 0.2, 0.0},
	{pTrianglePos[1].iX, pTrianglePos[1].iY + 0.2, 0.0},
};
GLfloat cfTriangle3[3][3] =
{
	{pTrianglePos[2].iX - 0.2, pTrianglePos[2].iY - 0.2, 0.0},
	{pTrianglePos[2].iX + 0.2, pTrianglePos[2].iY - 0.2, 0.0},
	{pTrianglePos[2].iX, pTrianglePos[2].iY + 0.2, 0.0},
};
GLfloat cfTriangle4[3][3] =
{
	{pTrianglePos[3].iX - 0.2, pTrianglePos[3].iY - 0.2, 0.0},
	{pTrianglePos[3].iX + 0.2, pTrianglePos[3].iY - 0.2, 0.0},
	{pTrianglePos[3].iX, pTrianglePos[3].iY + 0.2, 0.0},
};
const GLfloat cfColor1[3][3] =
{
	{1.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
	{1.0, 0.0, 0.0},
};
const GLfloat cfColor2[3][3] =
{
	{0.0, 1.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 1.0, 0.0},
};
const GLfloat cfColor3[3][3] =
{
	{0.0, 0.0, 1.0},
	{0.0, 0.0, 1.0},
	{0.0, 0.0, 1.0},
};
const GLfloat cfColor4[3][3] =
{
	{0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0},
};

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

GLvoid MakeVertexShader()
{
	GLchar* cVertexShaderSource = FileToBuf("Vertex_Shader_1.glsl");
	uiVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(uiVertexShader, 1, &cVertexShaderSource, NULL);
	glCompileShader(uiVertexShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(uiVertexShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(uiVertexShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Vertex Shader Compile Failed\n" << cErrorLog << std::endl;

		//return FALSE;
	}
}

GLvoid MakeFragmentShader()
{
	GLchar* cFragmentShaderSource = FileToBuf("Fragment_Shader_1.glsl");
	uiFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(uiFragmentShader, 1, &cFragmentShaderSource, NULL);
	glCompileShader(uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(uiFragmentShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(uiFragmentShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Fragment Shader Compile Failed\n" << cErrorLog << std::endl;

		//return FALSE;
	}
}

GLuint MakeShaderProgram()
{
	uiShaderProgramID = glCreateProgram();
	glAttachShader(uiShaderProgramID, uiVertexShader);
	glAttachShader(uiShaderProgramID, uiFragmentShader);
	glLinkProgram(uiShaderProgramID);

	glDeleteShader(uiVertexShader);
	glDeleteShader(uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetProgramiv(uiShaderProgramID, GL_LINK_STATUS, &iResult);

	if (!iResult)
	{
		glGetProgramInfoLog(uiShaderProgramID, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Shader Program Link Failed\n" << cErrorLog << std::endl;

		return FALSE;
	}

	glUseProgram(uiShaderProgramID);

	return uiShaderProgramID;
}

GLvoid InitializeBuffer()
{
	static BOOL bInitialize = FALSE;

	if (!bInitialize)
	{
		glGenVertexArrays(4, uiVAO);
		glGenBuffers(8, uiVBO);

		bInitialize = TRUE;
	}

	//1사분면
	glBindVertexArray(uiVAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfTriangle1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfColor1, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//2사분면
	glBindVertexArray(uiVAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfTriangle2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfColor2, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//3사분면
	glBindVertexArray(uiVAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[4]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfTriangle3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[5]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfColor3, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//4사분면
	glBindVertexArray(uiVAO[3]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[6]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfTriangle4, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[7]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), cfColor4, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

GLvoid InitializeShader()
{
	MakeVertexShader();
	MakeFragmentShader();
	uiShaderID = MakeShaderProgram();
}

GLvoid ChangePos(GLint i)
{
	switch (i)
	{
	case 0:
	{
		cfTriangle1[0][0] = pTrianglePos[0].iX - 0.2;
		cfTriangle1[0][1] = pTrianglePos[0].iY - 0.2;

		cfTriangle1[1][0] = pTrianglePos[0].iX + 0.2;
		cfTriangle1[1][1] = pTrianglePos[0].iY - 0.2;

		cfTriangle1[2][0] = pTrianglePos[0].iX;
		cfTriangle1[2][1] = pTrianglePos[0].iY + 0.2;

		break;
	}
	case 1:
	{
		cfTriangle2[0][0] = pTrianglePos[1].iX - 0.2;
		cfTriangle2[0][1] = pTrianglePos[1].iY - 0.2;

		cfTriangle2[1][0] = pTrianglePos[1].iX + 0.2;
		cfTriangle2[1][1] = pTrianglePos[1].iY - 0.2;

		cfTriangle2[2][0] = pTrianglePos[1].iX;
		cfTriangle2[2][1] = pTrianglePos[1].iY + 0.2;

		break;
	}
	case 2:
	{
		cfTriangle3[0][0] = pTrianglePos[2].iX - 0.2;
		cfTriangle3[0][1] = pTrianglePos[2].iY - 0.2;

		cfTriangle3[1][0] = pTrianglePos[2].iX + 0.2;
		cfTriangle3[1][1] = pTrianglePos[2].iY - 0.2;

		cfTriangle3[2][0] = pTrianglePos[2].iX;
		cfTriangle3[2][1] = pTrianglePos[2].iY + 0.2;

		break;
	}
	case 3:
	{
		cfTriangle4[0][0] = pTrianglePos[3].iX - 0.2;
		cfTriangle4[0][1] = pTrianglePos[3].iY - 0.2;

		cfTriangle4[1][0] = pTrianglePos[3].iX + 0.2;
		cfTriangle4[1][1] = pTrianglePos[3].iY - 0.2;

		cfTriangle4[2][0] = pTrianglePos[3].iX;
		cfTriangle4[2][1] = pTrianglePos[3].iY + 0.2;

		break;
	}
	default:
		break;
	}
}

GLvoid DrawScene()													// 콜백 함수 : 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							// 바탕색을 흰색으로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// 설정된 색으로 전체를 칠하기

	for (int i = 0; i < 4; ++i)
	{
		glUseProgram(uiShaderID);
		glBindVertexArray(uiVAO[i]);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
		glutSwapBuffers();												// 화면에 출력하기
}

GLvoid Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	static GLint i = 0;

	if (iButton == GLUT_LEFT_BUTTON && iState == GLUT_DOWN)
	{
		pTrianglePos[i].iX = (GLfloat)(iX - WINDOW_WIDTH / 2) / (WINDOW_WIDTH / 2);
		pTrianglePos[i].iY = (GLfloat)(WINDOW_HEIGHT / 2 - iY) / (WINDOW_HEIGHT / 2);

		ChangePos(i);

		i = (i + 1) % 4;
	}

	InitializeBuffer();
	glutPostRedisplay();
}

GLvoid Reshape(GLint iWidth, GLint iHeight)							// 콜백 함수 : 다시 그리기 콜백 함수
{
	glViewport(0, 0, iWidth, iHeight);
}