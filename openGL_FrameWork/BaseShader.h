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
	//월드 변환
	glm::mat4 mTranslate;			//이동 행렬
	RotateMat rmRotate;				//회전 행렬
	glm::mat4 mScale;				//신축 행렬
	glm::mat4 mWorld;				//월드 행렬
	GLuint uiWorldLocation;			//월드 변환 후 객체 위치

	//뷰 변환
	glm::mat4 mView;				//뷰 변환 행렬
	GLuint uiViewLocation;			//뷰 변환 우 객체 위치

	//투영 변환
	glm::mat4 mProjection;
	GLuint uiProjectionLocation;	//투영 변환 후 객체 위치

protected:
	//셰이더 속성
	Pos* pPos;
	Color* cColor;
	Index* iIndex;

	GLint iVertexNum;
	GLint iIndexNum;
protected:
	//월드변환 속성
	glm::vec3 vMove;
	Angle aDegree;
	glm::vec3 vSize;

	//뷰변환 속성
	glm::vec3 vPos;					//카메라 위치
	glm::vec3 vDirection;			//카메라의 방향벡터(n벡터)
	glm::vec3 vUp;					//v벡터

public:
	//생성자, 소멸자
	BaseShader();
	~BaseShader();
public:
	//Input 함수
	GLvoid InputVAO(GLuint VAO) { uiVAO = VAO; }

	//카메라 인자 카메라 클래스에서 받아오기
	GLvoid InputCameraPos(glm::vec3 vPos) { this->vPos = vPos; }
	GLvoid InputCameraDirection(glm::vec3 vDirection) { this->vDirection = vDirection; }
	GLvoid InputCameraUpVector(glm::vec3 vUp) { this->vUp = vUp; }
public:
	//Return 함수
	GLuint ReturnShaderID() { return uiShaderID; }
	GLuint ReturnVAO() { return uiVAO; }
	GLfloat Return(GLint i) { return pPos[i].X; }
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
	//순수 가상 함수
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