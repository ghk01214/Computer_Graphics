#include "pch.h"
#include "BaseShader.h"

BaseShader::BaseShader()
{
	mTranslate = glm::mat4(1.0f);
	mRotate = glm::mat4(1.0f);
	mScale = glm::mat4(1.0f);

	mWorld = glm::mat4(1.0f);
	mView = glm::mat4(1.0f);
	mProjection = glm::mat4(1.0f);

	MakeShader();
}

BaseShader::~BaseShader()
{
	if (vPos != GLM_NULLPTR)
	{
		delete[] vPos;
		vPos = GLM_NULLPTR;
	}

	if (vColor != GLM_NULLPTR)
	{
		delete[] vColor;
		vColor = GLM_NULLPTR;
	}

	if (uiIndex != GLM_NULLPTR)
	{
		delete[] uiIndex;
		uiIndex = GLM_NULLPTR;
	}
}

GLvoid BaseShader::MakeShader()
{
	GLint iResult;
	GLchar errorLog[512];

	GLchar* ShaderSource = ReadGLSL("Vertex_Shader.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &ShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: Vertex Shader Compile Failed\n" << errorLog << std::endl;
	}

	ShaderSource = ReadGLSL("Fragment_Shader.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &ShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &iResult);

	if (!iResult)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: Fragment Shader Compile Failed\n" << errorLog << std::endl;
	}

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &iResult);

	if (!iResult)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: Shader Program Link Failed\n" << errorLog << std::endl;
	}

	glGenVertexArrays(1, &(VAO));
	glGenBuffers(2, VBO);
	glGenBuffers(1, &EBO);
}
GLchar* BaseShader::ReadGLSL(const GLchar* fileName)
{
	FILE* file;
	GLulong length;
	GLchar* buffer;

	file = fopen(fileName, "rb");

	if (!file)
		return NULL;

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	buffer = (GLchar*)malloc(length + 1);
	fseek(file, 0, SEEK_SET);
	fread(buffer, length, 1, file);
	fclose(file);
	buffer[length] = 0;

	return buffer;

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

	vertexNum = iVertex;
	indexNum = iSide;

	vPos = new glm::vec3[vertexNum];
	vColor = new glm::vec3[vertexNum];
	uiIndex = new GLuint[indexNum * 3];

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
			fscanf(fObj, "%f %f %f", &vPos[iVertexIndex].x, &vPos[iVertexIndex].y, &vPos[iVertexIndex].z);

			++iVertexIndex;
		}

		if (cBind[0] == 'f' && cBind[1] == '\0')
		{
			fscanf(fObj, "%d %*c %*d %*c %*d %d %*c %*d %*c %*d %d", &uiIndex[iSideIndex], &uiIndex[iSideIndex + 1], &uiIndex[iSideIndex + 2]);

			uiIndex[iSideIndex] -= 1;
			uiIndex[iSideIndex + 1] -= 1;
			uiIndex[iSideIndex + 2] -= 1;

			iSideIndex += 3;
		}

		memset(cBind, '\0', sizeof(cBind));
	}

	fclose(fObj);
}

GLvoid BaseShader::InitializeBuffer()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexNum * sizeof(glm::vec3), vPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexNum * 3 * sizeof(GLuint), uiIndex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, vertexNum * sizeof(glm::vec3), vColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}
GLvoid BaseShader::Render()
{
	glUseProgram(shaderID);

	glEnable(GL_DEPTH_TEST);
	Transform();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexNum * 3, GL_UNSIGNED_INT, 0);
}

GLvoid BaseShader::Translate(glm::vec3 vMove)
{
	mTranslate = glm::translate(mTranslate, vMove);
	mWorld *= mTranslate;
	mTranslate = glm::mat4(1.0f);
}
GLvoid BaseShader::Rotate(glm::vec3 vAxis, GLfloat fDegree)
{
	mRotate = glm::rotate(mRotate, glm::radians(fDegree), vAxis);
	mWorld *= mRotate;
	mRotate = glm::mat4(1.0f);
}
GLvoid BaseShader::Scale(glm::vec3 vSize)
{
	mScale = glm::scale(mScale, vSize);
	mWorld *= mScale;
	mScale = glm::mat4(1.0f);
}

GLvoid BaseShader::View(Camera cView)
{
	mView = glm::lookAt(cView.ReturnPos(), cView.ReturnTarget(), cView.ReturnUp());
}

GLvoid BaseShader::Transform()
{
	//월드 변환
	worldLocation = glGetUniformLocation(shaderID, "mWorld");
	glUniformMatrix4fv(worldLocation, 1, GL_FALSE, glm::value_ptr(mWorld));

	//뷰 변환
	viewLocation = glGetUniformLocation(shaderID, "mView");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(mView));

	//투영 변환
	mProjection = glm::perspective(glm::radians(60.0f), (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
	projectionLocation = glGetUniformLocation(shaderID, "mProjection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(mProjection));
}