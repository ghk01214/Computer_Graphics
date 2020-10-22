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

GLchar* FileToBuf(const GLchar*);

class Shader
{
private:
	GLuint uiVertexShader;
	GLuint uiFragmentShader;
	GLuint uiShaderProgramID;
	GLuint uiShaderID;
public:
	Shader();
	GLuint ShaderID();
	GLvoid InputShaderID(GLuint);
	GLuint MakeVertexShader();
	GLuint MakeFragmentShader();
	GLuint MakeShaderProgram();
	~Shader();
};

Shader::Shader()
{

}
GLuint Shader::ShaderID()
{
	return Shader::uiShaderID;
}
GLvoid Shader::InputShaderID(GLuint ShaderID)
{
	Shader::uiShaderID = ShaderID;
}
GLuint Shader::MakeVertexShader()
{
	GLchar* cVertexShaderSource = FileToBuf("Vertex_Shader.glsl");
	Shader::uiVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Shader::uiVertexShader, 1, &cVertexShaderSource, NULL);
	glCompileShader(Shader::uiVertexShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(Shader::uiVertexShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(Shader::uiVertexShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Vertex Shader Compile Failed\n" << cErrorLog << std::endl;

		return FALSE;
	}
}
GLuint Shader::MakeFragmentShader()
{
	GLchar* cFragmentShaderSource = FileToBuf("Fragment_Shader.glsl");
	Shader::uiFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Shader::uiFragmentShader, 1, &cFragmentShaderSource, NULL);
	glCompileShader(Shader::uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(Shader::uiFragmentShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(Shader::uiFragmentShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Fragment Shader Compile Failed\n" << cErrorLog << std::endl;

		return FALSE;
	}
}
GLuint Shader::MakeShaderProgram()
{
	Shader::MakeVertexShader();
	Shader::MakeFragmentShader();

	Shader::uiShaderProgramID = glCreateProgram();
	glAttachShader(Shader::uiShaderProgramID, Shader::uiVertexShader);
	glAttachShader(Shader::uiShaderProgramID, Shader::uiFragmentShader);
	glLinkProgram(Shader::uiShaderProgramID);

	glDeleteShader(Shader::uiVertexShader);
	glDeleteShader(Shader::uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetProgramiv(Shader::uiShaderProgramID, GL_LINK_STATUS, &iResult);

	if (!iResult)
	{
		glGetProgramInfoLog(Shader::uiShaderProgramID, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Shader Program Link Failed\n" << cErrorLog << std::endl;

		return FALSE;
	}

	glUseProgram(Shader::uiShaderProgramID);

	return Shader::uiShaderProgramID;
}
Shader::~Shader()
{

}

Shader mMaster;

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

GLvoid InitializeShader()
{
	mMaster.InputShaderID(mMaster.MakeShaderProgram());
}