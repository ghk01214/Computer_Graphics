#pragma once
#include "define.h"
#include "Camera.h"

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
	glm::mat4 mRotate;				//ȸ�� ���
	glm::mat4 mScale;				//���� ���
	glm::mat4 mWorld;				//���� ���
	GLuint uiWorldLocation;			//���� ��ȯ �� ��ü ��ġ

	//�� ��ȯ
	glm::mat4 mView;				//�� ��ȯ ���
	GLuint uiViewLocation;			//�� ��ȯ �� ��ü ��ġ

	//���� ��ȯ
	glm::mat4 mProjection;			//���� ��ȯ ���
	GLuint uiProjectionLocation;	//���� ��ȯ �� ��ü ��ġ

protected:
	//���̴� �Ӽ�
	Pos* pPos;						//���� ��ǥ
	Color* cColor;					//���� ����
	Index* iIndex;					//���� �ε���

	GLint iVertexNum;				//���� ����
	GLint iIndexNum;				//�ε��� �ﰢ�� ����
protected:
	//���庯ȯ �Ӽ�
	glm::vec3 vMove;				//�̵���
	GLfloat fMove;					//�ະ �̵���

	glm::vec3 vAxis;				//ȸ�� ��
	GLfloat fDegree;				//�ະ ȸ����

	glm::vec3 vSize;				//���෮
	GLfloat fSize;					//�ະ ���෮
public:
	//������, �Ҹ���
	BaseShader();
	~BaseShader();
public:
	//Input �Լ�
	GLvoid InputVAO(GLuint VAO) { uiVAO = VAO; }

	//���� ��ȯ ���� Input �Լ�
	GLvoid InputTranslatePos(GLfloat fMove, GLchar cAxis, GLfloat fSign);			//��ü �̵��� Input
	GLvoid InputRotateAngle(GLfloat fDegree, GLchar cAxis, GLfloat fSign);			//��ü ȸ�� ���� Input
	GLvoid InputScaleSize(GLfloat fSize, GLchar cAxis, GLfloat fSign);				//��ü ���෮ Input

	GLvoid InputVertexNum(GLint iVertexNum) { this->iVertexNum = iVertexNum; }
	GLvoid InputIndexNum(GLint iIndexNum) { this->iIndexNum = iIndexNum; }

	//�� ��ȯ ���� Input �Լ�
	//GLvoid InputCameraPos(glm::vec3 vCameraPos) { this->vCameraPos = vCameraPos; }
	//GLvoid InputCameraDirection(glm::vec3 vCameraDirection) { this->vCameraDirection = vCameraDirection; }
	//GLvoid InputCameraUp(glm::vec3 vCameraUp) { this->vCameraUp = vCameraUp; }
public:
	//Return �Լ�
	GLuint ReturnShaderID() { return uiShaderID; }
	GLuint ReturnVAO() { return uiVAO; }

	GLint ReturnVertexNum() { return iVertexNum; }
	GLint ReturnIndexNum() { return iIndexNum; }
public:
	//���̴� ���� �Լ�
	GLuint MakeVertexShader();											//Vertex Shader ����
	GLuint MakeFragmentShader();										//Fragment Shader ����
	GLuint MakeShaderProgram();											//���̴� ���� ���α׷�
public:
	//���� ��ȯ �Լ�
	GLvoid TranslateWorld();											//�̵� ��ȯ
	GLvoid RotateWorld();												//ȸ�� ��ȯ
	GLvoid ScaleWorld();												//���� ��ȯ
	GLvoid ResetWorldTransform();										//���� ��ȯ �ʱ�ȭ

	//�� ��ȯ
	GLvoid MoveCamera(Camera cView);												//ī�޶� �̵�

	//��ü ��ȯ �Լ�
	GLvoid TransformShader();											//��ü ��ȯ
public:
	//���� ���� �Լ�
	virtual GLvoid InitializeBuffer() = 0;								//���� �ʱ�ȭ
	virtual GLvoid CreateObject(GLint iType, Pos pCenter) = 0;			//��ü ����
	virtual GLvoid Render() = 0;										//������
public:
	GLchar* ReadGLSL(const GLchar*);									//glsl ���� �б�
	GLvoid ReadObj(FILE*);												//obj ���� �б�
};