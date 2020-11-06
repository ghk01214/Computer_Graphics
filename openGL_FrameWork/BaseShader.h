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
	//���庯ȯ �Ӽ�
	glm::vec3 vMove;
	Angle aDegree;
	glm::vec3 vSize;

	//�亯ȯ �Ӽ�
	glm::vec3 vPos;					//ī�޶� ��ġ
	glm::vec3 vDirection;			//ī�޶��� ���⺤��(n����)
	glm::vec3 vUp;					//v����

public:
	//������, �Ҹ���
	BaseShader();
	~BaseShader();
public:
	//Input �Լ�
	GLvoid InputVAO(GLuint VAO) { uiVAO = VAO; }

	//ī�޶� ���� ī�޶� Ŭ�������� �޾ƿ���
	GLvoid InputCameraPos(glm::vec3 vPos) { this->vPos = vPos; }
	GLvoid InputCameraDirection(glm::vec3 vDirection) { this->vDirection = vDirection; }
	GLvoid InputCameraUpVector(glm::vec3 vUp) { this->vUp = vUp; }
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
	//���� ���� �Լ�
	virtual GLvoid InitializeBuffer() = 0;
	virtual GLvoid MakePolygon(GLint, Pos) = 0;
	virtual GLvoid Render() = 0;

	virtual GLvoid KeyDown(GLubyte, GLint, GLint) = 0;
	virtual GLvoid KeyUp(GLubyte, GLint, GLint) = 0;
	virtual GLvoid SpecialDown(GLint, GLint, GLint) = 0;
	virtual GLvoid SpecialUp(GLint, GLint, GLint) = 0;
public:
	GLchar* FileToBuf(const GLchar*);
	GLvoid ReadObj(FILE*);
};