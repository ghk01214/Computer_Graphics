#include "BaseShader.h"

BaseShader::BaseShader()
{
	BaseShader::uiVBO = new GLuint[VBO_NUM];

	BaseShader::mTranslate = glm::mat4(1.0f);
	BaseShader::rRotate = { glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f) };
	BaseShader::mScale = glm::mat4(1.0f);
	BaseShader::mWorld = glm::mat4(1.0f);
	BaseShader::uiModelLocation = 0;

	BaseShader::mInitTrans = glm::mat4(1.0f);
	BaseShader::rInitRotate = { glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f) };
	BaseShader::mInitScale = glm::mat4(1.0f);

	BaseShader::mInitTrans = BaseShader::mTranslate;
	BaseShader::rInitRotate = BaseShader::rRotate;
	BaseShader::mInitScale = BaseShader::mScale;

	BaseShader::vMove = { 0.0f, 0.0f, 0.0f };
	BaseShader::vSize = { 1.0f, 1.0f, 1.0f };
	BaseShader::aDegree = { 30.0f, -30.f, 0.0f };

	BaseShader::vInitMove = BaseShader::vMove;
	BaseShader::vInitSize = BaseShader::vSize;
	BaseShader::aInitDegree = BaseShader::aDegree;

	BaseShader::bTranslate = GL_TRUE;
	BaseShader::bRotate = GL_TRUE;
	BaseShader::bScale = GL_TRUE;
	BaseShader::bReset = GL_FALSE;
}

GLuint BaseShader::MakeVertexShader()
{
	GLchar* cVertexShaderSource = FileToBuf("Vertex_Shader.glsl");
	BaseShader::uiVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(BaseShader::uiVertexShader, 1, &cVertexShaderSource, NULL);
	glCompileShader(BaseShader::uiVertexShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(BaseShader::uiVertexShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(BaseShader::uiVertexShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Vertex Shader Compile Failed\n" << cErrorLog << std::endl;

		return GL_FALSE;
	}
}
GLuint BaseShader::MakeFragmentShader()
{
	GLchar* cFragmentShaderSource = BaseShader::FileToBuf("Fragment_Shader.glsl");
	BaseShader::uiFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(BaseShader::uiFragmentShader, 1, &cFragmentShaderSource, NULL);
	glCompileShader(BaseShader::uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetShaderiv(BaseShader::uiFragmentShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(BaseShader::uiFragmentShader, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Fragment Shader Compile Failed\n" << cErrorLog << std::endl;

		return GL_FALSE;
	}
}
GLuint BaseShader::MakeShaderProgram()
{
	BaseShader::MakeVertexShader();
	BaseShader::MakeFragmentShader();

	BaseShader::uiShaderID = glCreateProgram();
	glAttachShader(BaseShader::uiShaderID, BaseShader::uiVertexShader);
	glAttachShader(BaseShader::uiShaderID, BaseShader::uiFragmentShader);
	glLinkProgram(BaseShader::uiShaderID);

	glDeleteShader(BaseShader::uiVertexShader);
	glDeleteShader(BaseShader::uiFragmentShader);

	GLint iResult;
	GLchar cErrorLog[512];
	glGetProgramiv(BaseShader::uiShaderID, GL_LINK_STATUS, &iResult);

	if (!iResult)
	{
		glGetProgramInfoLog(BaseShader::uiShaderID, 512, NULL, cErrorLog);
		std::cerr << "ERROR: Shader Program Link Failed\n" << cErrorLog << std::endl;

		return GL_FALSE;
	}

	glGenVertexArrays(1, &(BaseShader::uiVAO));
	glGenBuffers(VBO_NUM, BaseShader::uiVBO);
	glGenBuffers(1, &(BaseShader::uiEBO));
}

GLvoid BaseShader::InputPos(Pos pTemp, GLint i)
{
	BaseShader::pPos[i] = pTemp;
}
GLvoid BaseShader::InputColor(Color cTemp, GLint i)
{
	BaseShader::cColor[i] = cTemp;
}
GLvoid BaseShader::InputIndex(Index iTemp, GLint i)
{
	BaseShader::iIndex[i] = iTemp;
}
GLvoid BaseShader::InputVertexNum(GLint iVertex)
{
	BaseShader::iVertexNum = iVertex;
}
GLvoid BaseShader::InputIndexNum(GLint Index)
{
	BaseShader::iIndexNum = Index;
}

GLvoid BaseShader::InputTranslateCoordinate(glm::vec3 vTranslate)
{
	BaseShader::vMove = vTranslate;
}
GLvoid BaseShader::InputRotationFactor(Angle Degree)
{
	BaseShader::aDegree = Degree;
}
GLvoid BaseShader::TranslateShader(BOOL bT)
{
	BaseShader::bTranslate = bT;
}
GLvoid BaseShader::RotateShader(BOOL bR)
{
	BaseShader::bRotate = bR;
}
GLvoid BaseShader::ScaleShader(BOOL bS)
{
	BaseShader::bScale = bS;
}

GLvoid BaseShader::InitializeBaseAttribute()
{
	BaseShader::pPos = new Pos[BaseShader::iVertexNum];
	BaseShader::cColor = new Color[BaseShader::iVertexNum];
	BaseShader::iIndex = new Index[BaseShader::iIndexNum];
}
GLvoid BaseShader::InitializeBuffer()
{
	glBindVertexArray(BaseShader::uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, BaseShader::uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, BaseShader::iVertexNum * sizeof(Pos), BaseShader::pPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BaseShader::uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, BaseShader::iIndexNum * sizeof(Index), BaseShader::iIndex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, BaseShader::uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, BaseShader::iVertexNum * sizeof(Color), BaseShader::cColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}
GLvoid BaseShader::Render()
{
	glUseProgram(BaseShader::uiShaderID);

	BaseShader::WorldTransform();

	glBindVertexArray(BaseShader::uiVAO);
	glDrawElements(GL_TRIANGLES, BaseShader::iIndexNum * 3, GL_UNSIGNED_INT, 0);
}

GLvoid BaseShader::Reset(BOOL Reset)
{
	BaseShader::bReset = Reset;
}

GLvoid BaseShader::WorldTransform()
{
	if (BaseShader::bReset)
	{
		BaseShader::mTranslate = BaseShader::mInitTrans;
		BaseShader::rRotate = BaseShader::rInitRotate;
		BaseShader::mScale = BaseShader::mInitScale;

		BaseShader::vMove = BaseShader::vInitMove;
		BaseShader::aDegree = BaseShader::aInitDegree;
		BaseShader::vSize = BaseShader::vInitSize;
	}

	if (BaseShader::bTranslate)
	{
		BaseShader::mTranslate = glm::translate(BaseShader::mTranslate, BaseShader::vMove);															//이동 변환
		BaseShader::bTranslate = GL_FALSE;
	}
	if (BaseShader::bRotate)
	{
		BaseShader::rRotate.mX = glm::rotate(BaseShader::rRotate.mX, glm::radians(BaseShader::aDegree.fX), glm::vec3(1.0f, 0.0f, 0.0f));			//X축 회전 변환
		BaseShader::rRotate.mY = glm::rotate(BaseShader::rRotate.mY, glm::radians(BaseShader::aDegree.fY), glm::vec3(0.0f, 1.0f, 0.0f));			//Y축 회전 변환
		BaseShader::rRotate.mZ = glm::rotate(BaseShader::rRotate.mZ, glm::radians(BaseShader::aDegree.fZ), glm::vec3(0.0f, 0.0f, 1.0f));			//Z축 회전 변환
		BaseShader::bRotate = GL_FALSE;
	}
	if (BaseShader::bScale)
	{
		BaseShader::mScale = glm::scale(BaseShader::mScale, BaseShader::vSize);																		//신축 변환
		BaseShader::bScale = GL_FALSE;
	}

	BaseShader::mWorld = BaseShader::mTranslate * BaseShader::rRotate.mX * BaseShader::rRotate.mY * BaseShader::rRotate.mZ;						//월드 변환

	BaseShader::uiModelLocation = glGetUniformLocation(BaseShader::uiShaderID, "mTransform");

	glUniformMatrix4fv(BaseShader::uiModelLocation, 1, GL_FALSE, glm::value_ptr(BaseShader::mWorld));
}
GLvoid BaseShader::ViewTransform()
{

}
GLvoid BaseShader::ProjectionTransform()
{

}
GLvoid BaseShader::VertexTransform()
{
	BaseShader::WorldTransform();
	BaseShader::ViewTransform();
	BaseShader::ProjectionTransform();
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

BaseShader::~BaseShader()
{
	delete[] BaseShader::uiVBO;
	delete[] BaseShader::pPos;
	delete[] BaseShader::cColor;
	delete[] BaseShader::iIndex;
}
