#include "BaseShader.h"

BaseShader::BaseShader()
{
	mTranslate = glm::mat4(1.0f);
	rmRotate = { glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f) };
	mScale = glm::mat4(1.0f);
	mWorld = glm::mat4(1.0f);

	mView = glm::mat4(1.0f);

	mProjection = glm::mat4(1.0f);

	uiWorldLocation = 0;

	vMove = { 0.0f, 0.0f, 0.0f };
	vSize = { 0.5f, 0.5f, 0.5f };
	aDegree = { 30.0f, 30.0f, 0.0f };

	vPos = { 0.0f, 0.0f, 3.0f };
	vDirection = { 0.0f, 0.0f, 0.0f };
	vUp = { 0.0f, 1.0f, 0.0f };

	MakeShaderProgram();
}

GLuint BaseShader::MakeVertexShader()
{
	GLchar* cVertexShaderSource = FileToBuf("Vertex_Shader.glsl");
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
	GLchar* cFragmentShaderSource = FileToBuf("Fragment_Shader.glsl");
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

GLvoid BaseShader::WorldTransform()
{
	mTranslate = glm::translate(mTranslate, vMove);														//이동 변환
	rmRotate.X = glm::rotate(rmRotate.X, glm::radians(aDegree.X), glm::vec3(1.0f, 0.0f, 0.0f));			//X축 회전 변환
	rmRotate.Y = glm::rotate(rmRotate.Y, glm::radians(aDegree.Y), glm::vec3(0.0f, 1.0f, 0.0f));			//Y축 회전 변환
	rmRotate.Z = glm::rotate(rmRotate.Z, glm::radians(aDegree.Z), glm::vec3(0.0f, 0.0f, 1.0f));			//Z축 회전 변환
	mScale = glm::scale(mScale, vSize);

	mWorld = mTranslate * rmRotate.X * rmRotate.Y * rmRotate.Z * mScale;								//월드 변환
	uiWorldLocation = glGetUniformLocation(uiShaderID, "mWorld");
	glUniformMatrix4fv(uiWorldLocation, 1, GL_FALSE, glm::value_ptr(mWorld));
}
GLvoid BaseShader::ViewTransform()
{
	mView = glm::lookAt(vPos, vDirection, vUp);

	uiViewLocation = glGetUniformLocation(uiShaderID, "mView");
	glUniformMatrix4fv(uiViewLocation, 1, GL_FALSE, glm::value_ptr(mView));
}
GLvoid BaseShader::ProjectionTransform()
{
	mProjection = glm::perspective(glm::radians(45.0f), (GLfloat)NUM::WINDOW_WIDTH / (GLfloat)NUM::WINDOW_HEIGHT, 1.0f, 200.0f);

	uiProjectionLocation = glGetUniformLocation(uiShaderID, "mProjection");
	glUniformMatrix4fv(uiProjectionLocation, 1, GL_FALSE, glm::value_ptr(mProjection));
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
GLvoid BaseShader::ReadObj(FILE* fObj)
{
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기 
	GLchar cCount[512];
	GLint iVertex = 0;
	GLint iSide = 0;

	while (!feof(fObj))
	{
		fscanf(fObj, "%s", cCount);

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

	iVertexNum = iVertex;
	iIndexNum = iSide;

	pPos = new Pos[iVertexNum];
	iIndex = new Index[iIndexNum];

	GLchar cBind[512];
	GLint iVertexIndex = 0;
	GLint iSideIndex = 0;
	GLint iNormalIndex = 0;

	fseek(fObj, 0, SEEK_SET);

	while (!feof(fObj))
	{
		fscanf(fObj, "%s", cBind);

		if (cBind[0] == 'v' && cBind[1] == '\0')
		{
			fscanf(fObj, "%f %f %f", &pPos[iVertexIndex].X, &pPos[iVertexIndex].Y, &pPos[iVertexIndex].Z);

			++iVertexIndex;
		}

		if (cBind[0] == 'f' && cBind[1] == '\0')
		{
			fscanf(fObj, "%d %*c %*d %*c %*d %d %*c %*d %*c %*d %d", &iIndex[iSideIndex].V1, &iIndex[iSideIndex].V2, &iIndex[iSideIndex].V3);

			iIndex[iSideIndex].V1 -= 1;
			iIndex[iSideIndex].V2 -= 1;
			iIndex[iSideIndex].V3 -= 1;

			++iSideIndex;
		}

		memset(cBind, '\0', sizeof(cBind));
	}

	fclose(fObj);
}

BaseShader::~BaseShader()
{

}