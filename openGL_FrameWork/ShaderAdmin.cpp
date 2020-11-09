#include "ShaderAdmin.h"

ShaderAdmin::ShaderAdmin()
{
	//for (GLint i = Manage::X; i <= Manage::Z; ++i)
	//{
	//	Pos temp = { 0.0f, 0.0f, 0.0f };
	//	bShader = new Shader1D(2);

	//	bShader->CreateObject(i, temp);
	//	vNorm.push_back(std::make_pair(bShader, std::make_pair(i, temp)));
	//}

	iShaderNum = -1;
	fSign = 1.0f;

	cView.InputRoateAngle(1.0f);
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
		case 's':
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
	case '-':
	{
		fSign = -1.0f;

		break;
	}
	//Ű�� ������ ���� �̵���ȯ ����
	case 'm':
	{
		vList[iShaderNum].first->InputTranslatePos(0.05f, cAxis, fSign);
		vList[iShaderNum].first->TranslateWorld();
		
		break;
	}
	//Ű�� ������ ���� ȸ����ȯ ����
	case 'r':
	{
		vList[iShaderNum].first->InputRotateAngle(10.0f, cAxis, fSign);
		vList[iShaderNum].first->RotateWorld();

		break;
	}
	//Ű�� ������ ���� ���ຯȯ
	case 'v':
	{
		vList[iShaderNum].first->InputScaleSize(1.0f, cAxis, fSign);
		vList[iShaderNum].first->ScaleWorld();

		break;
	}
	//Ű�� ������ ��ȯ �ʱ�ȭ �� ������ ��ġ
	case 'o':
	{
		vList[iShaderNum].first->ResetWorldTransform();

		break;
	}
	case 'k':
	{
		

		break;
	}
	case 'p':
	{


		break;
	}
	default:
		break;
	}
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
	case GLUT_KEY_LEFT:
	{
		cView.Rotate('y', -1);

		break;
	}
	case GLUT_KEY_RIGHT:
	{
		cView.Rotate('y', 1);

		break;
	}
	case GLUT_KEY_UP:
	{
		cView.Rotate('x', 1);

		break;
	}
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
		vList[i].first->MoveCamera(cView.ReturnCameraPos(), cView.ReturnCameraDirection(), cView.ReturnCameraUp());
	}
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
	vList[iShaderNum].first->MoveCamera(cView.ReturnCameraPos(), cView.ReturnCameraDirection(), cView.ReturnCameraUp());
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
}

ShaderAdmin::~ShaderAdmin()
{
	if (bShader != nullptr)
		delete bShader;
}