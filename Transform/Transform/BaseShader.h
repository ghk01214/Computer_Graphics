#pragma once
#include "struct.h"
#define WINDOW_POS_X 300
#define WINDOW_POS_Y 300
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VBO_NUM 2

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
	RotateMat rRotate;									//ȸ�� ���
	glm::mat4 mScale;									//���� ���
	glm::mat4 mWorld;									//���� ���
	GLuint uiModelLocation;
private:
	glm::vec3 vMove;									//�̵���
	Angle aDegree;										//ȸ�� ����
	glm::vec3 vSize;									//�����
	BOOL bRotate;
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
	GLvoid InputRotationFactor(Angle);
	GLvoid InputScaleSize(GLfloat, GLfloat, GLfloat);

	GLvoid ChangeRotation(BOOL b);
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