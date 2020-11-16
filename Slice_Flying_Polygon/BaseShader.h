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

protected:
	//셰이더 속성
	Pos* pPos;						//정점 좌표
	Color* cColor;					//정점 색상
	Index* iIndex;					//정점 인덱스

	GLint iVertexNum;				//정점 개수
	GLint iIndexNum;				//인덱스 삼각형 개수
protected:
	GLint iDirection;				//도형이 움직이는 방향

public:
	//생성자, 소멸자
	BaseShader();
	~BaseShader();
public:
	//Input 함수
	GLvoid InputVAO(GLuint VAO) { uiVAO = VAO; }
public:
	//Return 함수
	GLuint ReturnShaderID() { return uiShaderID; }
	GLuint ReturnVAO() { return uiVAO; }
public:
	//셰이더 생성 함수
	GLuint MakeVertexShader();											//Vertex Shader 생성
	GLuint MakeFragmentShader();										//Fragment Shader 생성
	GLuint MakeShaderProgram();											//셰이더 생성 프로그램
public:
	//순수 가상 함수
	virtual GLvoid InitializeBuffer() = 0;								//버퍼 초기화
	virtual GLvoid CreateObject(GLint iType, GLint iDirection) = 0;		//객체 생성
	virtual GLvoid Render() = 0;										//렌더링

	virtual GLvoid InputPos(Pos, GLint) = 0;
	virtual GLvoid InputColor(Color) = 0;
	virtual GLvoid InputCenter(Pos) = 0;
public:
	virtual Pos ReturnPos(GLint i) = 0;
	virtual Pos ReturnCenter() = 0;
public:
	GLchar* ReadGLSL(const GLchar*);									//glsl 파일 읽기
};