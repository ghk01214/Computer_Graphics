#include "ShaderAdmin.h"

ShaderAdmin::ShaderAdmin()
{
	iShaderNum = -1;
	fSign = 0.0f;

	pPlayer = new Player(cView);
}

//조작 중인 셰이더 정보 출력
GLvoid ShaderAdmin::PrintShaderInfo()
{

}

//키보드 입력
GLvoid ShaderAdmin::Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치

	//셰이더 번호 할당(10개의 셰이더를 수동으로 추가 가능)
	if (ubKey >= 48 && ubKey <= 57)
	{
		iShaderNum = ubKey - 48;
	}

	if (iShaderNum == vList.size())
	{
		switch (ubKey)
		{
		//사각형
		
		//원
		case 'C':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::X, pPos);
			break;
		}
		//사각뿔
		case 'p':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::Pyramid, pPos);

			break;
		}
		//원뿔
		case 'c':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::Cone, pPos);

			break;
		}
		//정육면체
		case 'h':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::Cube, pPos);

			break;
		}
		//구
		case 'g':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::Sphere, pPos);

			break;
		}
		default:
			break;
		}
	}

	switch (ubKey)
	{
	//변환 기준 축 정하기
	case 'x': case 'y': case 'z':
	{
		cAxis = ubKey;

		break;
	}
	//변환 방향 정하기
	case '+':
	{
		fSign = 1.0f;

		break;
	}
	case 'w':
	{
		cView.Move('z', 1);

		break;
	}
	case 'a':
	{
		cView.Move('x', -1);

		break;
	}
	case 's':
	{
		cView.Move('z', -1);

		break;
	}
	case 'd':
	{
		cView.Move('x', 1);

		break;
	}
	case '-':
	{
		fSign = -1.0f;

		break;
	}
	//키를 누르는 동안 신축변환
	case 'v':
	{
		vList[iShaderNum].first->InputScaleSize(0.1f, cAxis, fSign);
		vList[iShaderNum].first->ScaleWorld();

		break;
	}
	//키를 누르면 변환 초기화 후 원점에 위치
	case 'r':
	{
		vList[iShaderNum].first->ResetWorldTransform();

		break;
	}
	default:
		break;
	}

	for (GLint i = 0; i < vList.size(); ++i)
	{
		vList[i].first->MoveCamera(cView);
	}

	pPlayer->InputCameraAttribute(cView);
}

//ASCII가 아닌 특수 키 입력
GLvoid ShaderAdmin::Special(GLint iKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치

	/*
	KEY_MAP
	GLUT_KEY_F1 ~ GLUT_KEY_F12
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
	GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT, GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN
	*/

	switch (iKey)
	{
	//키를 누르는 동안 이동변환 적용
	case GLUT_KEY_PAGE_UP:
	{
		vList[iShaderNum].first->InputTranslatePos(0.05f, cAxis, fSign);
		vList[iShaderNum].first->TranslateWorld();

		break;
	}
	//키를 누르는 동안 회전변환 적용
	case GLUT_KEY_PAGE_DOWN:
	{
		vList[iShaderNum].first->InputRotateAngle(10.0f, cAxis, fSign);
		vList[iShaderNum].first->RotateWorld();

		break;
	}
	//카메라의 왼쪽 방향으로 회전
	case GLUT_KEY_LEFT:
	{
		cView.Rotate('y', -1);

		break;
	}
	//카메라의 오른쪽 방향으로 회전
	case GLUT_KEY_RIGHT:
	{
		cView.Rotate('y', 1);

		break;
	}
	//카메라의 위쪽 방향으로 회전
	case GLUT_KEY_UP:
	{
		cView.Rotate('x', 1);

		break;
	}
	//카메라의 아래쪽 방향으로 회전
	case GLUT_KEY_DOWN:
	{
		cView.Rotate('x', -1);

		break;
	}
	default:
		break;
	}

	for (GLint i = 0; i < vList.size(); ++i)
	{
		vList[i].first->MoveCamera(cView);
	}

	pPlayer->InputCameraAttribute(cView);
}

GLvoid ShaderAdmin::MakeShader(GLint iType, Pos pPos)
{
	switch (iType)
	{
	case Manage::X:
	{
		bShader = new Shader1D(3);
		break;
	}
	case Manage::Triangle:
	{
		bShader = new Shader2D(3);

		break;
	}
	case Manage::Square:
	{
		bShader = new Shader2D(4);

		break;
	}
	case Manage::Circle:
	{

		break;
	}
	case Manage::Pyramid:
	{
		bShader = new Shader3D(5);

		break;
	}
	case Manage::Cone:
	{
		bShader = new Shader3D(17);

		break;
	}
	case Manage::Cube:
	{
		bShader = new Shader3D(8);

		break;
	}
	case Manage::Sphere:
	{
		bShader = new Shader3D(482);

		break;
	}
	default:
		break;
	}

	vList.push_back(std::make_pair(bShader, std::make_pair(iType, pPos)));
	vList[iShaderNum].first->MoveCamera(cView);
}

GLvoid ShaderAdmin::Render()
{
	for (GLint i = 0; i < vNorm.size(); ++i)
	{
		vNorm[i].first->CreateObject(vNorm[i].second.first, vList[i].second.second);
	}
	for (GLint i = 0; i < vList.size(); ++i)
	{
		vList[i].first->CreateObject(vList[i].second.first, vList[i].second.second);
	}

	pPlayer->Render();
}

ShaderAdmin::~ShaderAdmin()
{
	if (bShader != GLM_NULLPTR)
	{
		delete bShader;
		bShader == GLM_NULLPTR;
	}

	if (pPlayer != GLM_NULLPTR)
	{
		delete pPlayer;
		pPlayer == GLM_NULLPTR;
	}
}