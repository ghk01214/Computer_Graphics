#include "ShaderAdmin.h"

ShaderAdmin::ShaderAdmin()
{
	iShaderNum = 0;
	fSign = 1.0f;

	vFlyingPolygon.reserve(6);
}

GLvoid ShaderAdmin::Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치

	switch (ubKey)
	{
	case 'l':
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}
	case 'f':
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
	//종료
	case 'Q': case 'q':
	{
		exit(0);
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid ShaderAdmin::Mouse(GLint iButton, GLint iState, GLint iX, GLint iY)
{
	//iButton = 버튼 파라미터(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
	//iState = 상태 파라미터(GLUT_UP, GLUT_DOWN)
	//iX, iY = 마우스 위치

	//마우스 위치 openGL 좌표로 정규화
	GLfloat fX = (GLfloat)(iX - glutGet(GLUT_WINDOW_WIDTH) / 2.0f) / ((GLfloat)glutGet(GLUT_WINDOW_WIDTH) / 2.0f);
	GLfloat fY = (GLfloat)(glutGet(GLUT_WINDOW_HEIGHT) / 2.0f - iY) / ((GLfloat)glutGet(GLUT_WINDOW_HEIGHT) / 2.0f);

	if (iButton == GLUT_LEFT_BUTTON)
	{
		switch (iState)
		{
		case GLUT_DOWN:
		{
			pMouseStart = std::make_pair(fX, fY);
			
			break;
		}
		case GLUT_UP:
		{
			delete s1CutTrack;
			s1CutTrack = nullptr;

			break;
		}
		default:
			break;
		}
	}

	glutPostRedisplay();
}
GLvoid ShaderAdmin::Motion(GLint iX, GLint iY)
{
	GLfloat fX = (GLfloat)(iX - glutGet(GLUT_WINDOW_WIDTH) / 2.0f) / ((GLfloat)glutGet(GLUT_WINDOW_WIDTH) / 2.0f);
	GLfloat fY = (GLfloat)(glutGet(GLUT_WINDOW_HEIGHT) / 2.0f - iY) / ((GLfloat)glutGet(GLUT_WINDOW_HEIGHT) / 2.0f);

	pMouseEnd = std::make_pair(fX, fY);

	if (pMouseStart != pMouseEnd && pMouseStart.second > -0.42f)
	{
		s1CutTrack = new Shader1D(2);
		Pos pStart = { pMouseStart.first, pMouseStart.second, 0.0f };
		Pos pEnd = { pMouseEnd.first, pMouseEnd.second, 0.0f };
		Color cColor = { 0.0f, 1.0f, 1.0f };
		s1CutTrack->InputPos(pStart, 0);
		s1CutTrack->InputPos(pEnd, 1);
		s1CutTrack->InputColor(cColor);
		s1CutTrack->CreateObject(Manage::Line, 0);
	}

	glutPostRedisplay();
}
GLvoid ShaderAdmin::Timer(GLint iValue)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<GLint> uDis(Manage::Triangle, Manage::Square);
	std::uniform_int_distribution<GLint> uDirec(Num::RT, Num::LB);

	//부유 도형을 최대 3개까지만 생성 가능하도록 설정
	if (vFlyingPolygon.size() < vFlyingPolygon.capacity())
	{
		iDirection = uDirec(mGen);
		MakeShader(uDis(mGen));
		MakeShader(Manage::Line);
	}

	glutPostRedisplay();
}

//3행 8열 공간 그리기
GLvoid ShaderAdmin::DrawSpace()
{
	Pos pCenter = { -0.875f, -0.5f, 0.0f };
	Pos pPos[4];

	for (GLint i = 0; i < 3; ++i)
	{
		for (GLint j = 0; j < 8; ++j)
		{
			pSpace[i][j].first = new Shader2D(4);
			pSpace[i][j].second = GL_FALSE;

			Color cColor = { 0.0f, 1.0f, 0.0f };

			pPos[0] = { pCenter.X - 0.1f, pCenter.Y + 0.08f, 0.0f };
			pPos[1] = { pCenter.X - 0.1f, pCenter.Y - 0.08f, 0.0f };
			pPos[2] = { pCenter.X + 0.1f, pCenter.Y - 0.08f, 0.0f };
			pPos[3] = { pCenter.X + 0.1f, pCenter.Y + 0.08f, 0.0f };

			if (i == 2)
			{
				pPos[1].Y += 0.02f;
				pPos[2].Y += 0.02f;
			}

			for (GLint k = 0; k < 4; ++k)
				pSpace[i][j].first->InputPos(pPos[k], k);

			pCenter.X += 0.25f;
			pSpace[i][j].first->InputColor(cColor);
			pSpace[i][j].first->CreateObject(Manage::Square, 0);
			pSpace[i][j].first->Render();
		}

		pCenter.X = -0.875f;
		pCenter.Y -= 0.2f;
	}
}

GLvoid ShaderAdmin::MakeShader(GLint iType)
{
	switch (iType)
	{
	case Manage::Line:
	{
		bShader = new Shader1D(2);

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
	default:
		break;
	}

	if (iType == Manage::Line)
		bShader->InputBarycenter(pBarycenter);
	bShader->CreateObject(iType, iDirection);
	if (iType != Manage::Line)
		pBarycenter = bShader->ReturnBarycenter();
	vFlyingPolygon.push_back(std::make_pair(bShader, std::make_pair(iType, iDirection)));
}

GLvoid ShaderAdmin::Render()
{
	//3행 8열 박스 그리기
	DrawSpace();

	//마우스 궤적 표시
	if (s1CutTrack != nullptr)
	{
		s1CutTrack->Render();
	}

	for (GLint i = 0; i < vFlyingPolygon.size(); ++i)
	{
		vFlyingPolygon[i].first->Render();
	}
}

ShaderAdmin::~ShaderAdmin()
{
	if (bShader != nullptr)
		delete bShader;
}