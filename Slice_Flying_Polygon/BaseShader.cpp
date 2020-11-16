#include "BaseShader.h"

BaseShader::BaseShader()
{
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