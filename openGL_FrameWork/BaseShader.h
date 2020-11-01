#pragma once
#include "define.h"

class BaseShader
{
private:
	//셰이더 생성 인자
	GLuint uiVertexShader;
	GLuint uiFragmentShader;
	GLuint uiShaderID;
private:
	//셰이더 버퍼 인자
	GLuint uiVAO;
private:
	//셰이더 변환 인자
	glm::mat4 mTranslate;			//이동 행렬
	RotateMat rmRotate;				//회전 행렬
	glm::mat4 mScale;				//신축 행렬
	glm::mat4 mWorld;				//월드 행렬
	GLuint uiModelLocation;

protected:
	//셰이더 속성
	Pos* pPos;
	Color* cColor;
	Index* iIndex;

	GLint iVertexNum;
	GLint iIndexNum;
protected:
	//변환 속성
	glm::vec3 vMove;
	Angle aDegree;
	glm::vec3 vSize;

public:
	//생성자, 소멸자
	BaseShader();
	~BaseShader();
public:
	//Input 함수
	GLvoid InputVAO(GLuint VAO) { this->uiVAO = VAO; }
public:
	//Return 함수
	GLuint ReturnShaderID() { return this->uiShaderID; }
	GLuint ReturnVAO() { return this->uiVAO; }
public:
	//셰이더 생성 함수
	GLuint MakeVertexShader();
	GLuint MakeFragmentShader();
	GLuint MakeShaderProgram();
public:
	//변환 함수
	GLvoid WorldTransform();			//월드 변환
	GLvoid ViewTransform();				//뷰 변환
	GLvoid ProjectionTransform();		//투영 변환

public:
	//
	virtual GLvoid InitializeBuffer() = 0;
	virtual GLvoid MakePolygon(GLint, Pos) = 0;
	virtual GLvoid Render() = 0;

public:
	GLchar* FileToBuf(const GLchar*);
};