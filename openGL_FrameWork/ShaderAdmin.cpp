#include "ShaderAdmin.h"

ShaderAdmin::ShaderAdmin()
{
	iShaderNum = -1;
	fSign = 0.0f;

	pPlayer = new Player(cView);
}

//���� ���� ���̴� ���� ���
GLvoid ShaderAdmin::PrintShaderInfo()
{

}

//Ű���� �Է�
GLvoid ShaderAdmin::Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = �Է� Ű����
	//iX, iY = Ű���� �Է� �� ���콺 ��ġ

	//���̴� ��ȣ �Ҵ�(10���� ���̴��� �������� �߰� ����)
	if (ubKey >= 48 && ubKey <= 57)
	{
		iShaderNum = ubKey - 48;
	}

	if (iShaderNum == vList.size())
	{
		switch (ubKey)
		{
		//�簢��
		
		//��
		case 'C':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::X, pPos);
			break;
		}
		//�簢��
		case 'p':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::Pyramid, pPos);

			break;
		}
		//����
		case 'c':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::Cone, pPos);

			break;
		}
		//������ü
		case 'h':
		{
			Pos pPos = { 0.0f, 0.0f, 0.0f };
			MakeShader(Manage::Cube, pPos);

			break;
		}
		//��
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
	//��ȯ ���� �� ���ϱ�
	case 'x': case 'y': case 'z':
	{
		cAxis = ubKey;

		break;
	}
	//��ȯ ���� ���ϱ�
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
	//Ű�� ������ ���� ���ຯȯ
	case 'v':
	{
		vList[iShaderNum].first->InputScaleSize(0.1f, cAxis, fSign);
		vList[iShaderNum].first->ScaleWorld();

		break;
	}
	//Ű�� ������ ��ȯ �ʱ�ȭ �� ������ ��ġ
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

//ASCII�� �ƴ� Ư�� Ű �Է�
GLvoid ShaderAdmin::Special(GLint iKey, GLint iX, GLint iY)
{
	//ubKey = �Է� Ű����
	//iX, iY = Ű���� �Է� �� ���콺 ��ġ

	/*
	KEY_MAP
	GLUT_KEY_F1 ~ GLUT_KEY_F12
	GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
	GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT, GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN
	*/

	switch (iKey)
	{
	//Ű�� ������ ���� �̵���ȯ ����
	case GLUT_KEY_PAGE_UP:
	{
		vList[iShaderNum].first->InputTranslatePos(0.05f, cAxis, fSign);
		vList[iShaderNum].first->TranslateWorld();

		break;
	}
	//Ű�� ������ ���� ȸ����ȯ ����
	case GLUT_KEY_PAGE_DOWN:
	{
		vList[iShaderNum].first->InputRotateAngle(10.0f, cAxis, fSign);
		vList[iShaderNum].first->RotateWorld();

		break;
	}
	//ī�޶��� ���� �������� ȸ��
	case GLUT_KEY_LEFT:
	{
		cView.Rotate('y', -1);

		break;
	}
	//ī�޶��� ������ �������� ȸ��
	case GLUT_KEY_RIGHT:
	{
		cView.Rotate('y', 1);

		break;
	}
	//ī�޶��� ���� �������� ȸ��
	case GLUT_KEY_UP:
	{
		cView.Rotate('x', 1);

		break;
	}
	//ī�޶��� �Ʒ��� �������� ȸ��
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