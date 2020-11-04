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
	//���� ��ȯ
	glm::mat4 mTranslate;			//�̵� ���
	RotateMat rmRotate;				//ȸ�� ���
	glm::mat4 mScale;				//���� ���
	glm::mat4 mWorld;				//���� ���
	GLuint uiWorldLocation;			//���� ��ȯ �� ��ü ��ġ

	//�� ��ȯ
	glm::mat4 mView;				//�� ��ȯ ���
	GLuint uiViewLocation;			//�� ��ȯ �� ��ü ��ġ

	//���� ��ȯ
	glm::mat4 mProjection;
	GLuint uiProjectionLocation;	//���� ��ȯ �� ��ü ��ġ

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

	glm::vec3 vPos;					//ī�޶� ��ġ

	glm::vec3 vTarget;				//ī�޶� �ٶ󺸴� ��ǥ
	glm::vec3 vDirection;			//ī�޶��� ���⺤��(n����)

	glm::vec3 vUPVec;				//UP ����
	glm::vec3 vRight;				//u����

	glm::vec3 vUp;					//v����


public:
	//������, �Ҹ���
	BaseShader();
	~BaseShader();
public:
	//Input �Լ�
	GLvoid InputVAO(GLuint VAO) { uiVAO = VAO; }
public:
	//Return �Լ�
	GLuint ReturnShaderID() { return uiShaderID; }
	GLuint ReturnVAO() { return uiVAO; }
	GLfloat Return(GLint i) { return pPos[i].X; }
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
	GLvoid ReadObj(FILE*);
};