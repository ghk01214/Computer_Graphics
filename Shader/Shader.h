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