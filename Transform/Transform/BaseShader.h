#pragma once
#include "struct.h"
#include <cstdbool>
#define WINDOW_POS_X 300
#define WINDOW_POS_Y 300
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VBO_NUM 2

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
	RotateMat rRotate;									//회전 행렬
	glm::mat4 mScale;									//신축 행렬
	glm::mat4 mWorld;									//월드 행렬

	glm::mat4 mInitTrans;
	RotateMat rInitRotate;
	glm::mat4 mInitScale;
	GLuint uiModelLocation;

	BOOL bReset;
private:
	glm::vec3 vMove;									//이동량
	Angle aDegree;										//회전 각도
	glm::vec3 vSize;									//신축률

	glm::vec3 vInitMove;
	Angle aInitDegree;
	glm::vec3 vInitSize;
private:
	BOOL bTranslate;
	BOOL bRotate;
	BOOL bScale;
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

	GLvoid InputTranslateCoordinate(glm::vec3);
	GLvoid InputRotationFactor(Angle);
	GLvoid InputScaleSize(GLfloat, GLfloat, GLfloat);

	GLvoid TranslateShader(BOOL);
	GLvoid RotateShader(BOOL);
	GLvoid ScaleShader(BOOL bS);
public:
	GLvoid InitializeBaseAttribute();
	GLvoid InitializeBuffer();
	GLvoid Render();
	GLvoid Reset(BOOL);
public:
	//변환 함수
	GLvoid WorldTransform();
	GLvoid ViewTransform();
	GLvoid ProjectionTransform();
	GLvoid VertexTransform();
public:
	GLchar* FileToBuf(const GLchar*);
};