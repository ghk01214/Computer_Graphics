#pragma once
#include "define.h"
#include "Camera.h"

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
	glm::mat4 mRotate;				//회전 행렬
	glm::mat4 mScale;				//신축 행렬
	glm::mat4 mWorld;				//월드 행렬
	GLuint uiWorldLocation;			//월드 변환 후 객체 위치

	//뷰 변환
	glm::mat4 mView;				//뷰 변환 행렬
	GLuint uiViewLocation;			//뷰 변환 우 객체 위치

	//투영 변환
	glm::mat4 mProjection;			//투영 변환 행렬
	GLuint uiProjectionLocation;	//투영 변환 후 객체 위치

protected:
	//셰이더 속성
	Pos* pPos;						//정점 좌표
	Color* cColor;					//정점 색상
	Index* iIndex;					//정점 인덱스

	GLint iVertexNum;				//정점 개수
	GLint iIndexNum;				//인덱스 삼각형 개수
protected:
	//월드변환 속성
	glm::vec3 vMove;				//이동량
	GLfloat fMove;					//축별 이동량

	glm::vec3 vAxis;				//회전 축
	GLfloat fDegree;				//축별 회전량

	glm::vec3 vSize;				//신축량
	GLfloat fSize;					//축별 신축량
public:
	//생성자, 소멸자
	BaseShader();
	~BaseShader();
public:
	//Input 함수
	GLvoid InputVAO(GLuint VAO) { uiVAO = VAO; }

	//월드 변환 인자 Input 함수
	GLvoid InputTranslatePos(GLfloat fMove, GLchar cAxis, GLfloat fSign);			//객체 이동량 Input
	GLvoid InputRotateAngle(GLfloat fDegree, GLchar cAxis, GLfloat fSign);			//객체 회전 각도 Input
	GLvoid InputScaleSize(GLfloat fSize, GLchar cAxis, GLfloat fSign);				//객체 신축량 Input

	GLvoid InputVertexNum(GLint iVertexNum) { this->iVertexNum = iVertexNum; }
	GLvoid InputIndexNum(GLint iIndexNum) { this->iIndexNum = iIndexNum; }

	//뷰 변환 인자 Input 함수
	//GLvoid InputCameraPos(glm::vec3 vCameraPos) { this->vCameraPos = vCameraPos; }
	//GLvoid InputCameraDirection(glm::vec3 vCameraDirection) { this->vCameraDirection = vCameraDirection; }
	//GLvoid InputCameraUp(glm::vec3 vCameraUp) { this->vCameraUp = vCameraUp; }
public:
	//Return 함수
	GLuint ReturnShaderID() { return uiShaderID; }
	GLuint ReturnVAO() { return uiVAO; }

	GLint ReturnVertexNum() { return iVertexNum; }
	GLint ReturnIndexNum() { return iIndexNum; }
public:
	//셰이더 생성 함수
	GLuint MakeVertexShader();											//Vertex Shader 생성
	GLuint MakeFragmentShader();										//Fragment Shader 생성
	GLuint MakeShaderProgram();											//셰이더 생성 프로그램
public:
	//월드 변환 함수
	GLvoid TranslateWorld();											//이동 변환
	GLvoid RotateWorld();												//회전 변환
	GLvoid ScaleWorld();												//신축 변환
	GLvoid ResetWorldTransform();										//월드 변환 초기화

	//뷰 변환
	GLvoid MoveCamera(Camera cView);												//카메라 이동

	//전체 변환 함수
	GLvoid TransformShader();											//전체 변환
public:
	//순수 가상 함수
	virtual GLvoid InitializeBuffer() = 0;								//버퍼 초기화
	virtual GLvoid CreateObject(GLint iType, Pos pCenter) = 0;			//객체 생성
	virtual GLvoid Render() = 0;										//렌더링
public:
	GLchar* ReadGLSL(const GLchar*);									//glsl 파일 읽기
	GLvoid ReadObj(FILE*);												//obj 파일 읽기
};