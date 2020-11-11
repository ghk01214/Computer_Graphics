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
	glm::mat4 mRotate;				//ȸ�� ���
	glm::mat4 mScale;				//���� ���
	glm::mat4 mWorld;				//���� ���
	GLuint uiWorldLocation;			//���� ��ȯ �� ��ü ��ġ

protected:
	//���̴� �Ӽ�
	Pos* pPos;						//���� ��ǥ
	Color* cColor;					//���� ����
	Index* iIndex;					//���� �ε���

	GLint iVertexNum;				//���� ����
	GLint iIndexNum;				//�ε��� �ﰢ�� ����
protected:
	GLint iDirection;				//������ �����̴� ����
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
public:
	//Return �Լ�
	GLuint ReturnShaderID() { return uiShaderID; }
	GLuint ReturnVAO() { return uiVAO; }
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

	//��ü ��ȯ �Լ�
	GLvoid TransformShader();											//��ü ��ȯ
public:
	//���� ���� �Լ�
	virtual GLvoid InitializeBuffer() = 0;								//���� �ʱ�ȭ
	virtual GLvoid CreateObject(GLint iType, GLint iDirection) = 0;		//��ü ����
	virtual GLvoid Render() = 0;										//������

	virtual GLvoid InputPos(Pos, GLint) = 0;
	virtual GLvoid InputColor(Color) = 0;
public:
	virtual GLvoid InputBarycenter(Pos pBarycenter) = 0;
	virtual Pos ReturnBarycenter() = 0;
public:
	GLchar* ReadGLSL(const GLchar*);									//glsl ���� �б�
};