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
	//���̴� ���� ����
	GLuint uiVertexShader;
	GLuint uiFragmentShader;
	GLuint uiShaderID;
private:
	//���̴� ����
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
	glm::mat4 mTranslate;								//�̵� ���
	glm::mat4 mRotate;									//ȸ�� ���
	glm::mat4 mScale;									//���� ���
	glm::mat4 mWorld;									//���� ���
	GLuint uiModelLocation;
private:
	glm::vec3 vMove;									//�̵���
	glm::vec3 vAxis;									//ȸ����
	GLfloat fDegree;									//ȸ�� ����
	glm::vec3 vSize;									//�����

public:
	BaseShader();
	~BaseShader();
public:
	//���̴� ����
	GLuint MakeVertexShader();
	GLuint MakeFragmentShader();
	GLuint MakeShaderProgram();
public:
	//Return �Լ�
public:
	//Input �Լ�
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
	//��ȯ �Լ�
	GLvoid WorldTransform();
	GLvoid ViewTransform();
	GLvoid ProjectionTransform();
	GLvoid VertexTransform();
public:
	GLchar* FileToBuf(const GLchar*);
};