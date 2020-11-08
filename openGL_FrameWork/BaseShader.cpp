#include "BaseShader.h"

BaseShader::BaseShader()
{
	mTranslate = glm::mat4(1.0f);
	mRotate = glm::mat4(1.0f);
	mScale = glm::mat4(1.0f);
	mWorld = glm::mat4(1.0f);

	mView = glm::lookAt(vCameraPos, vCameraDirection, vCameraUp);

	mProjection = glm::mat4(1.0f);

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

//뷰 변환 함수
GLvoid BaseShader::MoveCamera(glm::vec3 vCameraPos, glm::vec3 vCameraDirection, glm::vec3 vCameraUp)
{
	mView = glm::lookAt(vCameraPos, vCameraDirection, vCameraUp);
}

//전체 변환 함수
GLvoid BaseShader::TransformShader()
{
	//월드 변환
	uiWorldLocation = glGetUniformLocation(uiShaderID, "mWorld");
	glUniformMatrix4fv(uiWorldLocation, 1, GL_FALSE, glm::value_ptr(mWorld));

	//뷰 변환
	uiViewLocation = glGetUniformLocation(uiShaderID, "mView");
	glUniformMatrix4fv(uiViewLocation, 1, GL_FALSE, glm::value_ptr(mView));

	//투영 변환
	mProjection = glm::perspective(glm::radians(60.0f), (GLfloat)Num::WINDOW_WIDTH / (GLfloat)Num::WINDOW_HEIGHT, 0.1f, 100.0f);
	uiProjectionLocation = glGetUniformLocation(uiShaderID, "mProjection");
	glUniformMatrix4fv(uiProjectionLocation, 1, GL_FALSE, glm::value_ptr(mProjection));
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