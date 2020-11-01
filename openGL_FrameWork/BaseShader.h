#pragma once
#include "define.h"

class BaseShader
{
private:
	//���̴� ���� ����
	GLuint uiVertexShader;
	GLuint uiFragmentShader;
	GLuint uiShaderID;
private:
	//���̴� ���� ����
	GLuint uiVAO;
private:
	//���̴� ��ȯ ����
	glm::mat4 mTranslate;			//�̵� ���
	RotateMat rmRotate;				//ȸ�� ���
	glm::mat4 mScale;				//���� ���
	glm::mat4 mWorld;				//���� ���
	GLuint uiModelLocation;

protected:
	//���̴� �Ӽ�
	Pos* pPos;
	Color* cColor;
	Index* iIndex;

	GLint iVertexNum;
	GLint iIndexNum;
protected:
	//��ȯ �Ӽ�
	glm::vec3 vMove;
	Angle aDegree;
	glm::vec3 vSize;

public:
	//������, �Ҹ���
	BaseShader();
	~BaseShader();
public:
	//Input �Լ�
	GLvoid InputVAO(GLuint VAO) { this->uiVAO = VAO; }
public:
	//Return �Լ�
	GLuint ReturnShaderID() { return this->uiShaderID; }
	GLuint ReturnVAO() { return this->uiVAO; }
public:
	//���̴� ���� �Լ�
	GLuint MakeVertexShader();
	GLuint MakeFragmentShader();
	GLuint MakeShaderProgram();
public:
	//��ȯ �Լ�
	GLvoid WorldTransform();			//���� ��ȯ
	GLvoid ViewTransform();				//�� ��ȯ
	GLvoid ProjectionTransform();		//���� ��ȯ

public:
	//
	virtual GLvoid InitializeBuffer() = 0;
	virtual GLvoid MakePolygon(GLint, Pos) = 0;
	virtual GLvoid Render() = 0;

public:
	GLchar* FileToBuf(const GLchar*);
};