#include "ShaderAdmin.h"

ShaderAdmin::ShaderAdmin()
{
	iShaderNum = 0;
	fSign = 1.0f;

	iShowPath = 0;
	fSpeed = 0.01f;

	iCutPolygonNum = -1;
	bCutTimer = GL_FALSE;

	for (GLint i = 0; i < 2; ++i)
	{
		pCrossPoint[i] = { -10.0f, -10.0f, 0.0f };
	}

	for (GLint i = 0; i < 3; ++i)
	{
		for (GLint j = 0; j < 8; ++j)
		{
			pSpace[i][j].second = GL_FALSE;
		}
	}
}

GLvoid ShaderAdmin::Keyboard(GLubyte ubKey, GLint iX, GLint iY)
{
	//ubKey = 입력 키보드
	//iX, iY = 키보드 입력 시 마우스 위치

	switch (ubKey)
	{
	case 'l': case 'L':
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}
	case 'f': case 'F':
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
	case 'p': case 'P':
	{
		if (iShowPath == INT_MAX)
			iShowPath = 0;

		++iShowPath;
		break;
	}
	case '+':
	{
		fSpeed += 0.01f;
		break;
	}
	case '-':
	{
		if (fSpeed > 0.0f)
			fSpeed -= 0.01f;

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
	//마우스 위치를 openGL 좌표계에 맞춰 정규화
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
			FindCrossPoint();

			if (pCrossPoint[0].X != -10.0f)
			{
				for (GLint i = 0; i < 2; ++i)
					tempShader[i] = new Shader2D(3);

				for (GLint i = 0; i < 2; ++i)
				{
					tempCenter[i] = vFlyingPolygon[iCutPolygonNum].first->ReturnPos(i);
					tempShader[i]->InputCenter(tempCenter[i]);
					tempShader[i]->CreateObject(Manage::Triangle, 0);
				}

				vCutPolygon.push_back(std::make_pair(tempShader[0], tempShader[1]));
				vCutCenter.push_back(std::make_pair(tempCenter[0], tempCenter[1]));
				DeleteShader(iCutPolygonNum);

				bCutTimer = GL_TRUE;
			}

			delete s1CutTrack;
			s1CutTrack = GLM_NULLPTR;

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

	if (pMouseStart.second > -0.42f)
	{
		s1CutTrack = new Shader1D(2);
		Pos pStart = { pMouseStart.first, pMouseStart.second, 0.0f };
		Pos pEnd = { pMouseEnd.first, pMouseEnd.second, 0.0f };
		Color cColor = { 0.0f, 0.0f, 1.0f };
		s1CutTrack->InputPos(pStart, 0);
		s1CutTrack->InputPos(pEnd, 1);
		s1CutTrack->InputColor(cColor);
		s1CutTrack->CreateObject(Manage::Line, 0);
	}

	glutPostRedisplay();
}
GLvoid ShaderAdmin::TimerFunc(GLint iValue)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<GLint> uDis(Manage::Triangle, Manage::Square);
	std::uniform_int_distribution<GLint> uDirec(Num::RT, Num::LB);

	//부유 도형을 사전에 설정한 개수만 생성 가능하도록 설정
	if (vFlyingPolygon.size() < vFlyingPolygon.capacity())
	{
		iDirection = uDirec(mGen);
		MakeShader(uDis(mGen));
		MakeShader(Manage::Line);
	}

	glutPostRedisplay();
}
GLvoid ShaderAdmin::Timer(GLint iValue)
{
	//부유 도형 이동
	for (GLint i = 0; i < vFlyingPolygon.size() / 2; ++i)
	{
		switch (vFlyingPolygon[i * 2].second.second)
		{
		case Num::RT:
		{
			if ((vFlyingCenter[i].X >= vEnd[i].X || vFlyingCenter[i].Y >= vEnd[i].Y) && i < vFlyingPolygon.size() / 2 - 1)
				DeleteShader(i);
			else
				MovePolygon(1, i);

			break;
		}
		case Num::RB:
		{
			if ((vFlyingCenter[i].X >= vEnd[i].X || vFlyingCenter[i].Y <= vEnd[i].Y) && i < vFlyingPolygon.size() / 2 - 1)
				DeleteShader(i);
			else
				MovePolygon(1, i);

			break;
		}
		case Num::LT:
		{
			if ((vFlyingCenter[i].X <= vEnd[i].X || vFlyingCenter[i].Y >= vEnd[i].Y) && i < vFlyingPolygon.size() / 2 - 1)
				DeleteShader(i);
			else
				MovePolygon(-1, i);

			break;
		}
		case Num::LB:
		{
			if ((vFlyingCenter[i].X <= vEnd[i].X || vFlyingCenter[i].Y <= vEnd[i].Y) && i < vFlyingPolygon.size() / 2 - 1)
				DeleteShader(i);
			else
				MovePolygon(-1, i);

			break;
		}
		default:
			break;
		}
	}

	glutPostRedisplay();
}
GLvoid ShaderAdmin::FallTimer(GLint iValue)
{
	for (GLint i = 0; i <= vCutCenter.size() / 2; ++i)
	{
		vCutCenter[i].first.X += 0.001f;
		vCutCenter[i].first.Y -= 0.01f;
		vCutCenter[i].second.X -= 0.001f;
		vCutCenter[i].second.Y -= 0.01f;

		vCutPolygon[i].first->InputCenter(vCutCenter[i].first);
		vCutPolygon[i].first->CreateObject(Manage::Triangle, 0);
		vCutPolygon[i].second->InputCenter(vCutCenter[i].second);
		vCutPolygon[i].second->CreateObject(Manage::Triangle, 0);
	}

	glutPostRedisplay();
}

GLvoid ShaderAdmin::FindCrossPoint()
{
	for (GLint i = 0; i < vFlyingPolygon.size() / 2; ++i)
	{
		GLint iVertexNum = vFlyingPolygon[i * 2].second.first;

		for (GLint j = 0; j < iVertexNum; ++j)
		{
			GLfloat x1, x2, x3, x4;
			GLfloat y1, y2, y3, y4;

			x1 = pMouseStart.first;
			x2 = pMouseEnd.first;

			y1 = pMouseStart.second;
			y2 = pMouseEnd.second;

			if (j == iVertexNum - 1)
			{
				x3 = vFlyingPolygon[i * 2].first->ReturnPos(j).X;
				x4 = vFlyingPolygon[i * 2].first->ReturnPos(0).X;

				y3 = vFlyingPolygon[i * 2].first->ReturnPos(j).Y;
				y4 = vFlyingPolygon[i * 2].first->ReturnPos(0).Y;
			}
			else
			{
				x3 = vFlyingPolygon[i * 2].first->ReturnPos(j).X;
				x4 = vFlyingPolygon[i * 2].first->ReturnPos(j + 1).X;

				y3 = vFlyingPolygon[i * 2].first->ReturnPos(j).Y;
				y4 = vFlyingPolygon[i * 2].first->ReturnPos(j + 1).Y;
			}

			GLfloat numerator = (x4 - x3) * (y2 - y1) * x1 - (x2 - x1) * (y4 - y3) * x3 - (x2 - x1) * (x4 - x3) * (y1 - y3);
			GLfloat denominator = (x4 - x3) * (y2 - y1) - (x2 - x1) * (y4 - y3);

			GLfloat x = numerator / denominator;
			GLfloat y;

			switch (vFlyingPolygon[i * 2].second.first)
			{
			case Manage::Triangle:
			{
				if (j == 1)
				{
					if (x > x3 && x < x4)
					{
						y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;

						if (pCrossPoint[0].X == -10.0f)
						{
							pCrossPoint[0] = { x, y, 0.0f };
							iCutPolygonNum = i * 2;
						}
						else
							pCrossPoint[1] = { x, y, 0.0f };
					}
				}
				else
				{
					//교차점이 존재하면
					if (x > x4 && x < x3)
					{
						y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;

						if (pCrossPoint[0].X == -10.0f)
						{
							pCrossPoint[0] = { x, y, 0.0f };
							iCutPolygonNum = i * 2;
						}
						else
							pCrossPoint[1] = { x, y, 0.0f };
					}
				}

				break;
			}
			case Manage::Square:
			{
				if (j == 0 || j == 2)
				{
					if (x == x3)
					{
						y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;

						if (pCrossPoint[0].X == -10.0f)
						{
							pCrossPoint[0] = { x, y, 0.0f };
							iCutPolygonNum = i * 2;
						}
						else
							pCrossPoint[1] = { x, y, 0.0f };
					}
				}
				else
				{
					if (x > x3 && x < x4)
					{
						y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;

						if (pCrossPoint[0].X == -10.0f)
						{
							pCrossPoint[0] = { x, y, 0.0f };
							iCutPolygonNum = i * 2;
						}
						else
							pCrossPoint[1] = { x, y, 0.0f };
					}
				}

				break;
			}
			default:
				break;
			}
		}
	}
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
		bShader->InputPos(pTempStart, 0);

		break;
	}
	case Manage::Triangle: case Manage::Square:
	{
		bShader = new Shader2D(iType);

		break;
	}
	default:
		break;
	}

	bShader->CreateObject(iType, iDirection);

	if (iType != Manage::Line)
	{
		pTempStart = bShader->ReturnCenter();
		vStart.push_back(pTempStart);
		vFlyingCenter.push_back(pTempStart);
	}
	else
	{
		vEnd.push_back(bShader->ReturnPos(1));
	}

	vFlyingPolygon.push_back(std::make_pair(bShader, std::make_pair(iType, iDirection)));
}
GLvoid ShaderAdmin::MovePolygon(GLint iSign, GLint i)
{
	GLfloat fX = vFlyingCenter[i].X, fY = vFlyingCenter[i].Y;

	fX += iSign * fSpeed;
	fY = ((vEnd[i].Y - vStart[i].Y) / (vEnd[i].X - vStart[i].X)) * (fX - vStart[i].X) + vStart[i].Y;
	vFlyingCenter[i].X = fX;
	vFlyingCenter[i].Y = fY;

	vFlyingPolygon[i * 2].first->InputCenter(vFlyingCenter[i]);
	vFlyingPolygon[i * 2].first->CreateObject(vFlyingPolygon[i * 2].second.first, vFlyingPolygon[i * 2].second.second);
}
GLvoid ShaderAdmin::DeleteShader(GLint i)
{
	vStart.erase(vStart.begin() + i);
	vEnd.erase(vEnd.begin() + i);
	vFlyingCenter.erase(vFlyingCenter.begin() + i);

	delete vFlyingPolygon[i * 2].first;
	delete vFlyingPolygon[i * 2 + 1].first;
	vFlyingPolygon.erase(vFlyingPolygon.begin() + i * 2, vFlyingPolygon.begin() + i * 2 + 2);
}


GLvoid ShaderAdmin::Render()
{
	//3행 8열 박스 그리기
	DrawSpace();

	for (GLint i = 0; i < vFlyingPolygon.size() / 2; ++i)
	{
		if (iShowPath % 2 == 1)
			vFlyingPolygon[i * 2 + 1].first->Render();

		vFlyingPolygon[i * 2].first->Render();
	}

	if (bCutTimer)
	{
		for (GLint i = 0; i <= vCutPolygon.size() / 2; ++i)
		{
			vCutPolygon[i].first->Render();
			vCutPolygon[i].second->Render();
		}
	}

	//마우스 궤적 표시
	if (s1CutTrack != GLM_NULLPTR)
	{
		s1CutTrack->Render();
	}
}

ShaderAdmin::~ShaderAdmin()
{
	if (bShader != GLM_NULLPTR)
		delete bShader;
}