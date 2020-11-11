#include "BaseShader.h"

BaseShader::BaseShader()
{
	mTranslate = glm::mat4(1.0f);
	mRotate = glm::mat4(1.0f);
	mScale = glm::mat4(1.0f);
	mWorld = glm::mat4(1.0f);

	uiWorldLocation = 0;

	vMove = glm::vec3(0.0f, 0.0f, 0.0f);
	vAxis = glm::vec3(0.0f, 0.0f, 0.0f);
	vSize = glm::vec3(1.0f, 1.0f, 1.0f);
	fDegree = 0.0f;
	fMove = 0.0f;

	MakeShaderProgram();
}

//셰이더 생성 함수
GLuint BaseShader::MakeVertexShader()
{
	GLchar* cVertexShaderSource = ReadGLSL("Vertex_Shader.glsl");
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

		return GL_FALSE;
	}
}
GLuint BaseShader::MakeFragmentShader()
{
	GLchar* cFragmentShaderSource = ReadGLSL("Fragment_Shader.glsl");
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

		return GL_FALSE;
	}
}
GLuint BaseShader::MakeShaderProgram()
{
	MakeVertexShader();
	MakeFragmentShader();

	uiShaderID = glCreateProgram();
	glAttachShader(uiShaderID, uiVertexShader);
	glAttachShader(uiShaderID, uiFragmentShader);
	glLinkProgram(uiShaderID);

	glDeleteShader(uiVertexShader);
	glDeleteShader(uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetProgramiv(uiShaderID, GL_LINK_STATUS, &iResult);

	if (!iResult)
	{
		glGetProgramInfoLog(uiShaderID, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Shader Program Link Failed\n" << cErrorLog << std::endl;

		return GL_FALSE;
	}

	glGenVertexArrays(1, &(uiVAO));
}

//월드 변환 인자 Input 함수
GLvoid BaseShader::InputTranslatePos(GLfloat fMove, GLchar cAxis, GLfloat fSign)
{
	this->fMove = fSign * fMove;

	switch (cAxis)
	{
	case 'x':
	{
		vMove = glm::vec3(this->fMove, 0.0f, 0.0f);

		break;
	}
	case 'y':
	{
		vMove = glm::vec3(0.0f, this->fMove, 0.0f);

		break;
	}
	case 'z':
	{
		vMove = glm::vec3(0.0f, 0.0f, this->fMove);

		break;
	}
	default:
		break;
	}
}
GLvoid BaseShader::InputRotateAngle(GLfloat fDegree, GLchar cAxis, GLfloat fSign)
{
	this->fDegree = fSign * fDegree;

	switch (cAxis)
	{
	case 'x':
	{
		vAxis = glm::vec3(1.0f, 0.0f, 0.0f);

		break;
	}
	case 'y':
	{
		vAxis = glm::vec3(0.0f, 1.0f, 0.0f);

		break;
	}
	case 'z':
	{
		vAxis = glm::vec3(0.0f, 0.0f, 1.0f);

		break;
	}
	default:
		break;
	}
}
GLvoid BaseShader::InputScaleSize(GLfloat fSize, GLchar cAxis, GLfloat fSign)
{
	this->fSize = fSign * fSize;

	switch (cAxis)
	{
	case 'x':
	{
		vSize = glm::vec3(this->fSize, 0.0f, 0.0f);

		break;
	}
	case 'y':
	{
		vSize = glm::vec3(0.0f, this->fSize, 0.0f);

		break;
	}
	case 'z':
	{
		vSize = glm::vec3(0.0f, 0.0f, this->fSize);

		break;
	}
	default:
		break;
	}
}

//월드 변환 함수
GLvoid BaseShader::TranslateWorld()
{
	mTranslate = glm::translate(mTranslate, vMove);
	mWorld = mWorld * mTranslate;
	mTranslate = glm::mat4(1.0f);
}
GLvoid BaseShader::RotateWorld()
{
	mRotate = glm::rotate(mRotate, glm::radians(fDegree), vAxis);
	mWorld = mWorld * mRotate;
	mRotate = glm::mat4(1.0f);
}
GLvoid BaseShader::ScaleWorld()
{
	mScale = glm::scale(mScale, vSize);
	mWorld = mWorld * mScale;
	mScale = glm::mat4(1.0f);
}
GLvoid BaseShader::ResetWorldTransform()
{
	mWorld = glm::mat4(1.0f);
}

//전체 변환 함수
GLvoid BaseShader::TransformShader()
{
	//월드 변환
	uiWorldLocation = glGetUniformLocation(uiShaderID, "mWorld");
	glUniformMatrix4fv(uiWorldLocation, 1, GL_FALSE, glm::value_ptr(mWorld));
}

GLchar* BaseShader::ReadGLSL(const GLchar* cFile)
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

BaseShader::~BaseShader()
{

}