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
	glm::mat4 mTranslate;		//이동 행렬
	glm::mat4 mRotate;			//회전 행렬
	glm::mat4 mScale;			//신축 행렬

	glm::mat4 mWorld;			//월드 행렬
	glm::mat4 mView;			//뷰 행렬
	glm::mat4 mProjection;		//투영 행렬

	GLuint worldLocation;
	GLuint viewLocation;
	GLuint projectionLocation;

protected:
	glm::vec3* vPos;			//정점 좌표
	glm::vec3* vColor;			//정점 색상
	GLuint* uiIndex;			//정점 인덱스 번호

	GLuint vertexNum;			//정점 개수
	GLuint indexNum;			//인덱스 삼각형 개수
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