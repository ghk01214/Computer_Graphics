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

protected:
	//���̴� �Ӽ�
	Pos* pPos;						//���� ��ǥ
	Color* cColor;					//���� ����
	Index* iIndex;					//���� �ε���

	GLint iVertexNum;				//���� ����
	GLint iIndexNum;				//�ε��� �ﰢ�� ����
protected:
	GLint iDirection;				//������ �����̴� ����

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
public:
	//���̴� ���� �Լ�
	GLuint MakeVertexShader();											//Vertex Shader ����
	GLuint MakeFragmentShader();										//Fragment Shader ����
	GLuint MakeShaderProgram();											//���̴� ���� ���α׷�
public:
	//���� ���� �Լ�
	virtual GLvoid InitializeBuffer() = 0;								//���� �ʱ�ȭ
	virtual GLvoid CreateObject(GLint iType, GLint iDirection) = 0;		//��ü ����
	virtual GLvoid Render() = 0;										//������

	virtual GLvoid InputPos(Pos, GLint) = 0;
	virtual GLvoid InputColor(Color) = 0;
	virtual GLvoid InputCenter(Pos) = 0;
public:
	virtual Pos ReturnPos(GLint i) = 0;
	virtual Pos ReturnCenter() = 0;
public:
	GLchar* ReadGLSL(const GLchar*);									//glsl ���� �б�
};