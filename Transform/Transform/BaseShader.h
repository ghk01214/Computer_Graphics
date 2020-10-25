#pragma once
#include "header.h"
#define WINDOW_POS_X 300
#define WINDOW_POS_Y 300
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VBO_NUM 2

struct Pos
{
	GLfloat fX, fY, fZ;
};

struct Color
{
	GLfloat fR, fG, fB;
};

struct Index
{
	GLuint uiV1, uiV2, uiV3;
};

class BaseShader
{
private:
	//셰이더 생성 인자
	GLuint uiVertexShader;
	GLuint uiFragmentShader;
	GLuint uiShaderID;
private:
	//셰이더 버퍼
	GLuint uiVAO;
	GLuint* uiVBO;
	GLuint uiEBO;
private:
	Pos* pPos;
	Color* cColor;
	Index* iIndex;

	GLint iVertexNum;
	GLint iIndexNum;
private:
	glm::mat4 mTranslate;								//이동 행렬
	glm::mat4 mRotate;									//회전 행렬
	glm::mat4 mScale;									//신축 행렬
	glm::mat4 mWorld;									//월드 행렬
	GLuint uiModelLocation;
private:
	glm::vec3 vMove;									//이동량
	glm::vec3 vAxis;									//회전축
	GLfloat fDegree;									//회전 각도
	glm::vec3 vSize;									//신축률

public:
	BaseShader();
	~BaseShader();
public:
	//셰이더 생성
	GLuint MakeVertexShader();
	GLuint MakeFragmentShader();
	GLuint MakeShaderProgram();
public:
	//Return 함수
public:
	//Input 함수
	GLvoid InputPos(Pos, GLint);
	GLvoid InputColor(Color, GLint);
	GLvoid InputIndex(Index, GLint);
	GLvoid InputVertexNum(GLint);
	GLvoid InputIndexNum(GLint);

	GLvoid InputTranslateCoordinate(GLfloat, GLfloat, GLfloat);
	GLvoid InputRotationFactor(GLfloat, GLfloat, GLfloat, GLfloat);
	GLvoid InputScaleSize(GLfloat, GLfloat, GLfloat);
public:
	GLvoid InitializeBaseAttribute();
	GLvoid InitializeBuffer();
	GLvoid Render();
public:
	//변환 함수
	GLvoid WorldTransform();
	GLvoid ViewTransform();
	GLvoid ProjectionTransform();
	GLvoid VertexTransform();
public:
	GLchar* FileToBuf(const GLchar*);
};