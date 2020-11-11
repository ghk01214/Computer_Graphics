#include "Shader2D.h"

Shader2D::Shader2D(GLint k)
{
	pPos = new Pos[k];
	cColor = new Color[k];
	iIndex = new Index[k - 2];

	iVertexNum = k;
	iIndexNum = k - 2;

	glGenBuffers(Num::VBO, uiVBO);
	glGenBuffers(1, &(uiEBO));
}

GLvoid Shader2D::InputPos(Pos pPos, GLint i)
{
	this->pPos[i] = pPos;
}
GLvoid Shader2D::InputColor(Color cColor)
{
	for (GLint i = 0; i < iVertexNum; ++i)
	{
		this->cColor[i] = cColor;
	}
}

GLvoid Shader2D::CreateObject(GLint iType, GLint iDirection)
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());

	switch (iType)
	{
	case Manage::Triangle:
	{
		switch (iDirection)
		{
		case Num::RT:
		{
			std::uniform_real_distribution<GLfloat> uX(-2.0f, -1.0f);
			std::uniform_real_distribution<GLfloat> uY(-0.42f, 0.58f);

			pPos[0] = { uX(mGen), uY(mGen), 0.0f };
			pPos[1] = { uX(mGen), uY(mGen), 0.0f };

			if (pPos[0].X < pPos[1].X)
			{
				std::uniform_real_distribution<GLfloat> uX(-2.0f, pPos[1].X);

				if (pPos[0].Y < pPos[1].Y)
				{
					std::uniform_real_distribution<GLfloat> uY(pPos[1].Y, 0.58f);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
				else
				{
					std::uniform_real_distribution<GLfloat> uY(pPos[0].Y, 0.58f);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
			}
			else
			{
				std::uniform_real_distribution<GLfloat> uX(-2.0f, pPos[0].X);

				if (pPos[0].Y < pPos[1].Y)
				{
					std::uniform_real_distribution<GLfloat> uY(-0.42f, pPos[0].Y);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
				else
				{
					std::uniform_real_distribution<GLfloat> uY(-0.42f, pPos[1].Y);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
			}

			break;
		}
		case Num::LT:
		{
			std::uniform_real_distribution<GLfloat> uX(1.0f, 2.0f);
			std::uniform_real_distribution<GLfloat> uY(-0.42f, 0.58f);

			pPos[0] = { uX(mGen), uY(mGen), 0.0f };
			pPos[1] = { uX(mGen), uY(mGen), 0.0f };

			if (pPos[0].X < pPos[1].X)
			{
				std::uniform_real_distribution<GLfloat> uX(1.0f, pPos[1].X);

				if (pPos[0].Y < pPos[1].Y)
				{
					std::uniform_real_distribution<GLfloat> uY(pPos[1].Y, 0.58f);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
				else
				{
					std::uniform_real_distribution<GLfloat> uY(pPos[0].Y, 0.58f);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
			}
			else
			{
				std::uniform_real_distribution<GLfloat> uX(1.0f, pPos[0].X);

				if (pPos[0].Y < pPos[1].Y)
				{
					std::uniform_real_distribution<GLfloat> uY(-0.42f, pPos[0].Y);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
				else
				{
					std::uniform_real_distribution<GLfloat> uY(-0.42f, pPos[1].Y);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
			}

			break;
		}
		case Num::RB:
		{
			std::uniform_real_distribution<GLfloat> uX(-2.0f, -1.0f);
			std::uniform_real_distribution<GLfloat> uY(0.0f, 1.0f);

			pPos[0] = { uX(mGen), uY(mGen), 0.0f };
			pPos[1] = { uX(mGen), uY(mGen), 0.0f };

			if (pPos[0].X < pPos[1].X)
			{
				std::uniform_real_distribution<GLfloat> uX(-2.0f, pPos[1].X);

				if (pPos[0].Y < pPos[1].Y)
				{
					std::uniform_real_distribution<GLfloat> uY(pPos[1].Y, 1.0f);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
				else
				{
					std::uniform_real_distribution<GLfloat> uY(pPos[0].Y, 1.0f);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
			}
			else
			{
				std::uniform_real_distribution<GLfloat> uX(-2.0f, pPos[0].X);

				if (pPos[0].Y < pPos[1].Y)
				{
					std::uniform_real_distribution<GLfloat> uY(-0.0f, pPos[0].Y);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
				else
				{
					std::uniform_real_distribution<GLfloat> uY(-0.0f, pPos[1].Y);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
			}

			break;
		}
		case Num::LB:
		{
			std::uniform_real_distribution<GLfloat> uX(1.0f, 2.0f);
			std::uniform_real_distribution<GLfloat> uY(0.0f, 1.0f);

			pPos[0] = { uX(mGen), uY(mGen), 0.0f };
			pPos[1] = { uX(mGen), uY(mGen), 0.0f };

			if (pPos[0].X < pPos[1].X)
			{
				std::uniform_real_distribution<GLfloat> uX(1.0f, pPos[1].X);

				if (pPos[0].Y < pPos[1].Y)
				{
					std::uniform_real_distribution<GLfloat> uY(pPos[1].Y, 0.58f);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
				else
				{
					std::uniform_real_distribution<GLfloat> uY(pPos[0].Y, 0.58f);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
			}
			else
			{
				std::uniform_real_distribution<GLfloat> uX(1.0f, pPos[0].X);

				if (pPos[0].Y < pPos[1].Y)
				{
					std::uniform_real_distribution<GLfloat> uY(-0.42f, pPos[0].Y);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
				else
				{
					std::uniform_real_distribution<GLfloat> uY(-0.42f, pPos[1].Y);
					pPos[2] = { uX(mGen), uY(mGen), 0.0f };
				}
			}

			break;
		}
		default:
			break;
		}

		pBarycenter.X = (pPos[0].X + pPos[1].X + pPos[2].X) / 3.0f;
		pBarycenter.Y = (pPos[0].Y + pPos[1].Y + pPos[2].Y) / 3.0f;

		//삼각형
		iIndex[0] = { 0, 1, 2 };

		break;
	}
	case Manage::Square:
	{
		if (pPos == nullptr)
		{
			switch (iDirection)
			{
			case Num::RT:
			{
				std::uniform_real_distribution<GLfloat> uX(-2.0f, -1.0f);
				std::uniform_real_distribution<GLfloat> uY(-0.42f, 0.58f);

				pPos[0] = { uX(mGen), uY(mGen), 0.0f };
				pPos[1] = { uX(mGen), uY(mGen), 0.0f };

				if (pPos[0].X < pPos[1].X)
				{
					if (pPos[0].Y < pPos[1].Y)
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[0].X, pPos[1].X);
						std::uniform_real_distribution<GLfloat> uY2(pPos[1].Y, 0.58f);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(-2.0f, pPos[0].X);
						std::uniform_real_distribution<GLfloat> uY3(pPos[0].Y, pPos[2].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
					else
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[1].X, -1.0f);
						std::uniform_real_distribution<GLfloat> uY2(pPos[1].Y, pPos[0].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[0].X, pPos[2].X);
						std::uniform_real_distribution<GLfloat> uY3(pPos[0].Y, 0.58f);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
				}
				else
				{
					if (pPos[0].Y < pPos[1].Y)
					{
						std::uniform_real_distribution<GLfloat> uX2(-2.0f, pPos[1].X);
						std::uniform_real_distribution<GLfloat> uY2(pPos[0].Y, pPos[1].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[2].X, pPos[0].X);
						std::uniform_real_distribution<GLfloat> uY3(-0.42f, pPos[0].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
					else
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[1].X, -1.0f);
						std::uniform_real_distribution<GLfloat> uY2(-0.42f, pPos[1].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[2].X, -1.0f);
						std::uniform_real_distribution<GLfloat> uY3(pPos[2].Y, pPos[0].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
				}

				break;
			}
			case Num::LT:
			{
				std::uniform_real_distribution<GLfloat> uX(1.0f, 2.0f);
				std::uniform_real_distribution<GLfloat> uY(-0.42f, 0.58f);

				pPos[0] = { uX(mGen), uY(mGen), 0.0f };
				pPos[1] = { uX(mGen), uY(mGen), 0.0f };

				if (pPos[0].X < pPos[1].X)
				{
					if (pPos[0].Y < pPos[1].Y)
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[0].X, pPos[1].X);
						std::uniform_real_distribution<GLfloat> uY2(pPos[1].Y, 0.58f);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(1.0f, pPos[0].X);
						std::uniform_real_distribution<GLfloat> uY3(pPos[0].Y, pPos[2].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
					else
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[1].X, 2.0f);
						std::uniform_real_distribution<GLfloat> uY2(pPos[1].Y, pPos[0].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[0].X, pPos[2].X);
						std::uniform_real_distribution<GLfloat> uY3(pPos[0].Y, 0.58f);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
				}
				else
				{
					if (pPos[0].Y < pPos[1].Y)
					{
						std::uniform_real_distribution<GLfloat> uX2(1.0f, pPos[1].X);
						std::uniform_real_distribution<GLfloat> uY2(pPos[0].Y, pPos[1].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[2].X, pPos[0].X);
						std::uniform_real_distribution<GLfloat> uY3(-0.42f, pPos[0].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
					else
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[1].X, 2.0f);
						std::uniform_real_distribution<GLfloat> uY2(-0.42f, pPos[1].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[2].X, 2.0f);
						std::uniform_real_distribution<GLfloat> uY3(pPos[2].Y, pPos[0].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
				}

				break;
			}
			case Num::RB:
			{
				std::uniform_real_distribution<GLfloat> uX(-2.0f, -1.0f);
				std::uniform_real_distribution<GLfloat> uY(0.0f, 1.0f);

				pPos[0] = { uX(mGen), uY(mGen), 0.0f };
				pPos[1] = { uX(mGen), uY(mGen), 0.0f };

				if (pPos[0].X < pPos[1].X)
				{
					if (pPos[0].Y < pPos[1].Y)
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[0].X, pPos[1].X);
						std::uniform_real_distribution<GLfloat> uY2(pPos[1].Y, 1.0f);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(-2.0f, pPos[0].X);
						std::uniform_real_distribution<GLfloat> uY3(pPos[0].Y, pPos[2].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
					else
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[1].X, -1.0f);
						std::uniform_real_distribution<GLfloat> uY2(pPos[1].Y, pPos[0].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[0].X, pPos[2].X);
						std::uniform_real_distribution<GLfloat> uY3(pPos[0].Y, 1.0f);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
				}
				else
				{
					if (pPos[0].Y < pPos[1].Y)
					{
						std::uniform_real_distribution<GLfloat> uX2(-2.0f, pPos[1].X);
						std::uniform_real_distribution<GLfloat> uY2(pPos[0].Y, pPos[1].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[2].X, pPos[0].X);
						std::uniform_real_distribution<GLfloat> uY3(0.0f, pPos[0].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
					else
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[1].X, -1.0f);
						std::uniform_real_distribution<GLfloat> uY2(0.0f, pPos[1].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[2].X, -1.0f);
						std::uniform_real_distribution<GLfloat> uY3(pPos[2].Y, pPos[0].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
				}

				break;
			}
			case Num::LB:
			{
				std::uniform_real_distribution<GLfloat> uX(1.0f, 2.0f);
				std::uniform_real_distribution<GLfloat> uY(0.0f, 1.0f);

				pPos[0] = { uX(mGen), uY(mGen), 0.0f };
				pPos[1] = { uX(mGen), uY(mGen), 0.0f };

				if (pPos[0].X < pPos[1].X)
				{
					if (pPos[0].Y < pPos[1].Y)
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[0].X, pPos[1].X);
						std::uniform_real_distribution<GLfloat> uY2(pPos[1].Y, 1.0f);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(1.0f, pPos[0].X);
						std::uniform_real_distribution<GLfloat> uY3(pPos[0].Y, pPos[2].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
					else
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[1].X, 2.0f);
						std::uniform_real_distribution<GLfloat> uY2(pPos[1].Y, pPos[0].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[0].X, pPos[2].X);
						std::uniform_real_distribution<GLfloat> uY3(pPos[0].Y, 1.0f);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
				}
				else
				{
					if (pPos[0].Y < pPos[1].Y)
					{
						std::uniform_real_distribution<GLfloat> uX2(1.0f, pPos[1].X);
						std::uniform_real_distribution<GLfloat> uY2(pPos[0].Y, pPos[1].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[2].X, pPos[0].X);
						std::uniform_real_distribution<GLfloat> uY3(0.0f, pPos[0].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
					else
					{
						std::uniform_real_distribution<GLfloat> uX2(pPos[1].X, 2.0f);
						std::uniform_real_distribution<GLfloat> uY2(0.0f, pPos[1].Y);
						pPos[2] = { uX2(mGen), uY2(mGen), 0.0f };

						std::uniform_real_distribution<GLfloat> uX3(pPos[2].X, 2.0f);
						std::uniform_real_distribution<GLfloat> uY3(pPos[2].Y, pPos[0].Y);
						pPos[3] = { uX3(mGen), uY3(mGen), 0.0f };
					}
				}

				break;
			}
			default:
				break;
			}
		}

		pBarycenter.X = (pPos[0].X + pPos[1].X + pPos[2].X + pPos[3].X) / 4.0f;
		pBarycenter.Y = (pPos[0].Y + pPos[1].Y + pPos[2].Y + pPos[3].Y) / 4.0f;

		//사각형
		iIndex[0] = { 0, 1, 2 };
		iIndex[1] = { 0, 2, 3 };

		break;
	}
	default:
		break;
	}

	if (cColor == nullptr)
	{
		for (GLint i = 0; i < iVertexNum; ++i)
		{
			cColor[i] = { 1.0f, 1.0f, 1.0f };
		}
	}

	pBarycenter.Z = 0.0f;

	InitializeBuffer();
}

GLvoid Shader2D::InitializeBuffer()
{
	uiVAO = ReturnVAO();

	glBindVertexArray(uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, iVertexNum * sizeof(Pos), pPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iIndexNum * sizeof(Index), iIndex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, iVertexNum * sizeof(Color), cColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	InputVAO(uiVAO);
}

GLvoid Shader2D::Render()
{
	glUseProgram(ReturnShaderID());

	TransformShader();

	glBindVertexArray(ReturnVAO());
	glDrawElements(GL_TRIANGLES, iIndexNum * 3, GL_UNSIGNED_INT, 0);
}

Shader2D::~Shader2D()
{
	delete[] pPos;
	delete[] cColor;
	delete[] iIndex;
}