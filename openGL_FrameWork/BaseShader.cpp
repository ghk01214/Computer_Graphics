#include "BaseShader.h"

BaseShader::BaseShader()
{
	this->mTranslate = glm::mat4(1.0f);
	this->rmRotate = { glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f) };
	this->mScale = glm::mat4(1.0f);
	this->mWorld = glm::mat4(1.0f);
	this->uiModelLocation = 0;

	this->vMove = { 0.0f, 0.0f, 0.0f };
	this->vSize = { 1.0f, 1.0f, 1.0f };
	this->aDegree = { 30.0f, -30.f, 0.0f };

	this->MakeShaderProgram();
}

GLuint BaseShader::MakeVertexShader()
{
	GLchar* cVertexShaderSource = FileToBuf("Vertex_Shader.glsl");
	this->uiVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->uiVertexShader, 1, &cVertexShaderSource, NULL);
	glCompileShader(this->uiVertexShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(this->uiVertexShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(this->uiVertexShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Vertex Shader Compile Failed\n" << cErrorLog << std::endl;

		return GL_FALSE;
	}
}
GLuint BaseShader::MakeFragmentShader()
{
	GLchar* cFragmentShaderSource = this->FileToBuf("Fragment_Shader.glsl");
	this->uiFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->uiFragmentShader, 1, &cFragmentShaderSource, NULL);
	glCompileShader(this->uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(this->uiFragmentShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(this->uiFragmentShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Fragment Shader Compile Failed\n" << cErrorLog << std::endl;

		return GL_FALSE;
	}
}
GLuint BaseShader::MakeShaderProgram()
{
	this->MakeVertexShader();
	this->MakeFragmentShader();

	this->uiShaderID = glCreateProgram();
	glAttachShader(this->uiShaderID, this->uiVertexShader);
	glAttachShader(this->uiShaderID, this->uiFragmentShader);
	glLinkProgram(this->uiShaderID);

	glDeleteShader(this->uiVertexShader);
	glDeleteShader(this->uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetProgramiv(this->uiShaderID, GL_LINK_STATUS, &iResult);

	if (!iResult)
	{
		glGetProgramInfoLog(this->uiShaderID, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Shader Program Link Failed\n" << cErrorLog << std::endl;

		return GL_FALSE;
	}

	glGenVertexArrays(1, &(this->uiVAO));
}

GLvoid BaseShader::WorldTransform()
{
	this->mTranslate = glm::translate(this->mTranslate, this->vMove);														//이동 변환
	this->rmRotate.X = glm::rotate(this->rmRotate.X, glm::radians(this->aDegree.X), glm::vec3(1.0f, 0.0f, 0.0f));			//X축 회전 변환
	this->rmRotate.Y = glm::rotate(this->rmRotate.Y, glm::radians(this->aDegree.Y), glm::vec3(0.0f, 1.0f, 0.0f));			//Y축 회전 변환
	this->rmRotate.Z = glm::rotate(this->rmRotate.Z, glm::radians(this->aDegree.Z), glm::vec3(0.0f, 0.0f, 1.0f));			//Z축 회전 변환
	this->mScale = glm::scale(this->mScale, this->vSize);

	this->mWorld = this->mTranslate * this->rmRotate.X * this->rmRotate.Y * this->rmRotate.Z;								//월드 변환
	this->uiModelLocation = glGetUniformLocation(this->uiShaderID, "mTransform");
	glUniformMatrix4fv(this->uiModelLocation, 1, GL_FALSE, glm::value_ptr(this->mWorld));
}
GLvoid BaseShader::ViewTransform()
{
	
}
GLvoid BaseShader::ProjectionTransform()
{
	
}

GLchar* BaseShader::FileToBuf(const GLchar* cFile)
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
GLvoid BaseShader::ReadObj(FILE* fObjFile)
{
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기 
	GLchar cCount[512];
	GLint iVertex = 0;
	GLint iSide = 0;

	while (!feof(fObjFile))
	{
		fscanf(fObjFile, "%s", cCount);

		if (cCount[0] == 'v' && cCount[1] == '\0')
		{
			++iVertex;
		}

		if (cCount[0] == 'f' && cCount[1] == '\0')
		{
			++iSide;
		}

		memset(cCount, '\0', sizeof(cCount));
	}

	this->iVertexNum = iVertex;
	this->iIndexNum = iSide;

	this->pPos = new Pos[this->iVertexNum];
	this->iIndex = new Index[this->iIndexNum];

	GLchar cBind[512];
	GLint iVertexIndex = 0;
	GLint iSideIndex = 0;
	GLint iNormalIndex = 0;

	fseek(fObjFile, 0, SEEK_SET);

	while (!feof(fObjFile))
	{
		fscanf(fObjFile, "%s", cBind);

		if (cBind[0] == 'v' && cBind[1] == '\0')
		{
			fscanf(fObjFile, "%f %f %f", &this->pPos[this->iVertexNum].X, &this->pPos[this->iVertexNum].Y, &this->pPos[this->iVertexNum].Z);

			++iVertexIndex;
		}

		if (cBind[0] == 'f' && cBind[1] == '\0')
		{
			fscanf(fObjFile, "%d %*c %*d %*c %*d %d %*c %*d %*c %*d %d", &this->iIndex[iSideIndex].V1, &this->iIndex[iSideIndex].V2, &this->iIndex[iSideIndex].V3);

			++iSideIndex;
		}

		memset(cBind, '\0', sizeof(cBind));
	}

	fclose(fObjFile);
}

BaseShader::~BaseShader()
{

}