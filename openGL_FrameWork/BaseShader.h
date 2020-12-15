#pragma once
#include "Camera.h"

class BaseShader
{
private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderID;
private:
	GLuint VAO;
	GLuint VBO[2];
	GLuint EBO;
private:
	glm::mat4 mTranslate;		//�̵� ���
	glm::mat4 mRotate;			//ȸ�� ���
	glm::mat4 mScale;			//���� ���

	glm::mat4 mWorld;			//���� ���
	glm::mat4 mView;			//�� ���
	glm::mat4 mProjection;		//���� ���

	GLuint worldLocation;
	GLuint viewLocation;
	GLuint projectionLocation;

protected:
	glm::vec3* vPos;			//���� ��ǥ
	glm::vec3* vColor;			//���� ����
	GLuint* uiIndex;			//���� �ε��� ��ȣ

	GLuint vertexNum;			//���� ����
	GLuint indexNum;			//�ε��� �ﰢ�� ����
public:
	BaseShader();
	~BaseShader();
public:
	glm::vec3 ReturnOnePos(GLint i) { return vPos[i]; }
public:
	GLvoid MakeShader();
	GLchar* ReadGLSL(const GLchar* cFile);
	GLvoid ReadObj(FILE* fObj);
public:
	virtual GLvoid InitializeBuffer();
	virtual GLvoid Render();
public:
	GLvoid Translate(glm::vec3 vector);
	GLvoid Rotate(glm::vec3 vector, GLfloat degree);
	GLvoid Scale(glm::vec3 vector);
	
	GLvoid View(Camera cView);

	GLvoid Transform();
public:
	virtual GLvoid CreateObject(GLint iType) = 0;
	virtual GLvoid CreateObject(GLint iType, glm::vec3 color) = 0;
public:
	enum Type
	{
		Cube, Sphere, Cone
	};
};