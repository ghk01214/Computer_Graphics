#include "pch.h"
#include "RunTime_FrameWork.h"

RunTime_FrameWork::RunTime_FrameWork()
{
	pPlayer = new Player(cView);

	viewPoint = Back;
}

RunTime_FrameWork::~RunTime_FrameWork()
{
	delete pPlayer;
	pPlayer = GLM_NULLPTR;
}

GLvoid RunTime_FrameWork::MakeShader()
{
	pPlayer->ModelPlayer(cView);
}

GLvoid RunTime_FrameWork::Render()
{
	pPlayer->Render();
}

GLvoid RunTime_FrameWork::KeyboardDown(GLubyte key, GLint x, GLint y)
{
	//key = 입력 키
	//x, y = 입력 시 마우스 위치\

	static GLint temp = 0;

	switch (key)
	{
	case 'W': case 'w':
	{
		cView.Move(cView.Forward, 0.1f);

		break;
	}
	case 'S': case 's':
	{
		cView.Move(cView.Backward, 0.1f);
		break;
	}
	case 'D': case 'd':
	{
		//if (temp % 2 == 1)
		if (viewPoint != Top)
			cView.Rotate(1);
		//else
			pPlayer->Rotate(-1);
	
		break;
	}
	case 'A': case 'a':
	{
		//if (temp % 2 == 1)
		if (viewPoint != Top)
			cView.Rotate(-1);
		//else
			pPlayer->Rotate(1);
	}
		break;
	case 'C': case 'c':
	{
		//++temp;

		break;
	}
	case 'F': case 'f':
	{
		cView.InputPos(glm::vec3(pPlayer->ReturnPos().x, 0.0f, pPlayer->ReturnPos().z + 5.0f));
		cView.InputTarget(glm::vec3(pPlayer->ReturnTarget().x, 0.0f, pPlayer->ReturnTarget().z));
		cView.InputUp(glm::vec3(0.0f, 1.0f, 0.0f));
		cView.InputDirection(pPlayer->ReturnDirection());
		viewPoint = Front;
		break;
	}
	case 'B': case 'b':
	{
		cView.InputPos(glm::vec3(pPlayer->ReturnPos().x, 4.0f, pPlayer->ReturnPos().z));
		cView.InputTarget(glm::vec3(pPlayer->ReturnTarget().x, 0.0f, pPlayer->ReturnTarget().z));
		cView.InputUp(glm::vec3(0.0f, 1.0f, 0.0f));
		cView.InputDirection(pPlayer->ReturnDirection());
		viewPoint = Back;
		break;
	}
	case 'T': case 't':
	{
		cView.InputPos(glm::vec3(pPlayer->ReturnPos().x, 7.0f, pPlayer->ReturnPos().z + 5.0f));
		cView.InputTarget(glm::vec3(pPlayer->ReturnTarget().x, 0.0f, pPlayer->ReturnTarget().z));
		cView.InputUp(glm::vec3(0.0f, 0.0f, 1.0f));
		cView.InputDirection(pPlayer->ReturnDirection());
		viewPoint = Top;

		break;
	}
	case 'Q': case 'q':
	{
		exit(0);
		break;
	}
	default:
		break;
	}

	pPlayer->View(cView);
}

GLvoid RunTime_FrameWork::SpecialKeyDown(GLint key, GLint x, GLint y)
{
	//key = 입력 키
	//x, y = 입력 시 마우스 위치

	GLfloat playerSpeed = 0.2f;
	GLfloat cameraSpeed = 0.273f;

	switch (key)
	{
	case GLUT_KEY_UP:
	{
		cView.Move(cView.Forward, cameraSpeed);
		pPlayer->Move(pPlayer->Forward, playerSpeed);

		break;
	}
	case GLUT_KEY_DOWN:
	{
		cView.Move(cView.Backward, cameraSpeed);
		pPlayer->Move(pPlayer->Backward, playerSpeed);

		break;
	}
	case GLUT_KEY_LEFT:
	{
		cView.Move(cView.Left, cameraSpeed);
		pPlayer->Move(pPlayer->Left, playerSpeed);

		break;
	}
	case GLUT_KEY_RIGHT:
	{
		cView.Move(cView.Right, cameraSpeed);
		pPlayer->Move(pPlayer->Right, playerSpeed);

		break;
	}
	default:
		break;
	}

	pPlayer->View(cView);
}