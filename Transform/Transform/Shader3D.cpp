#include "Shader3D.h"

Shader3D::Shader3D()
{

}

GLvoid Shader3D::InitializeAttribute(GLint iVertex)
{
	Shader3D::iVertexNum = iVertex;
	Shader3D::InputVertexNum(Shader3D::iVertexNum);
	Shader3D::InputIndexNum(2 * Shader3D::iVertexNum - 4);

	Shader3D::pPos = new Pos[Shader3D::iVertexNum];
	Shader3D::cColor = new Color[Shader3D::iVertexNum];
	Shader3D::iIndex = new Index[2 * Shader3D::iVertexNum - 4];
}

GLvoid Shader3D::DrawPolygon(Pos Coord, GLint iType)
{
	switch (iType)
	{
	case PYRAMID:
	{
		Shader3D::InitializeAttribute(5);
		Shader3D::DrawPyramid(Coord);
		
		break;
	}
	case HEXA:
	{
		Shader3D::InitializeAttribute(8);
		Shader3D::DrawHexahedron(Coord);

		break;
	}
	default:
		break;
	}

	Shader3D::InitializeBaseAttribute();

	for (GLint i = 0; i < 2 * Shader3D::iVertexNum - 4; ++i)
	{
		if (i < Shader3D::iVertexNum)
		{
			Shader3D::InputPos(Shader3D::pPos[i], i);
			Shader3D::InputColor(Shader3D::cColor[i], i);
		}

		Shader3D::InputIndex(Shader3D::iIndex[i], i);
	}

	Shader3D::InitializeBuffer();
	Shader3D::Render();
}

GLvoid Shader3D::DrawPyramid(Pos Coord)
{
	Shader3D::pPos[0] = { Coord.fX, Coord.fY + 0.2f, Coord.fZ };
	Shader3D::pPos[1] = { Coord.fX - 0.2f, Coord.fY - 0.2f, Coord.fZ - 0.2f };
	Shader3D::pPos[2] = { Coord.fX + 0.2f, Coord.fY - 0.2f, Coord.fZ - 0.2f };
	Shader3D::pPos[3] = { Coord.fX + 0.2f, Coord.fY - 0.2f, Coord.fZ + 0.2f };
	Shader3D::pPos[4] = { Coord.fX - 0.2f, Coord.fY - 0.2f, Coord.fZ + 0.2f };

	Shader3D::cColor[0] = { 1.0f, 1.0f, 1.0f };
	Shader3D::cColor[1] = { 0.0f, 1.0f, 0.0f };
	Shader3D::cColor[2] = { 0.0f, 0.0f, 0.0f };
	Shader3D::cColor[3] = { 0.0f, 0.0f, 1.0f };
	Shader3D::cColor[4] = { 1.0f, 0.0f, 0.0f };

	Shader3D::iIndex[0] = { 0, 1, 2 };
	Shader3D::iIndex[1] = { 0, 2, 3 };
	Shader3D::iIndex[2] = { 0, 3, 4 };
	Shader3D::iIndex[3] = { 0, 4, 1 };
	Shader3D::iIndex[4] = { 1, 4, 3 };
	Shader3D::iIndex[5] = { 1, 3, 2 };
}

GLvoid Shader3D::DrawHexahedron(Pos Coord)
{
	Shader3D::pPos[0] = { Coord.fX - 0.2f, Coord.fY + 0.2f, Coord.fZ - 0.2f };
	Shader3D::pPos[1] = { Coord.fX - 0.2f, Coord.fY - 0.2f, Coord.fZ - 0.2f };
	Shader3D::pPos[2] = { Coord.fX + 0.2f, Coord.fY - 0.2f, Coord.fZ - 0.2f };
	Shader3D::pPos[3] = { Coord.fX + 0.2f, Coord.fY + 0.2f, Coord.fZ - 0.2f };
	Shader3D::pPos[4] = { Coord.fX - 0.2f, Coord.fY + 0.2f, Coord.fZ + 0.2f };
	Shader3D::pPos[5] = { Coord.fX - 0.2f, Coord.fY - 0.2f, Coord.fZ + 0.2f };
	Shader3D::pPos[6] = { Coord.fX + 0.2f, Coord.fY - 0.2f, Coord.fZ + 0.2f };
	Shader3D::pPos[7] = { Coord.fX + 0.2f, Coord.fY + 0.2f, Coord.fZ + 0.2f };

	Shader3D::cColor[0] = { 0.0f, 1.0f, 1.0f };
	Shader3D::cColor[1] = { 0.0f, 0.0f, 1.0f };
	Shader3D::cColor[2] = { 1.0f, 0.0f, 1.0f };
	Shader3D::cColor[3] = { 1.0f, 1.0f, 1.0f };
	Shader3D::cColor[4] = { 0.0f, 1.0f, 0.0f };
	Shader3D::cColor[5] = { 0.0f, 0.0f, 0.0f };
	Shader3D::cColor[6] = { 1.0f, 0.0f, 0.0f };
	Shader3D::cColor[7] = { 1.0f, 1.0f, 0.0f };

	Shader3D::iIndex[0] = { 0, 1, 2 };
	Shader3D::iIndex[1] = { 0, 2, 3 };
	Shader3D::iIndex[2] = { 4, 0, 3 };
	Shader3D::iIndex[3] = { 4, 3, 7 };
	Shader3D::iIndex[4] = { 7, 6, 5 };
	Shader3D::iIndex[5] = { 7, 5, 4 };
	Shader3D::iIndex[6] = { 1, 5, 6 };
	Shader3D::iIndex[7] = { 1, 6, 2 };
	Shader3D::iIndex[8] = { 4, 5, 1 };
	Shader3D::iIndex[9] = { 4, 1, 0 };
	Shader3D::iIndex[10] = { 3, 2, 6 };
	Shader3D::iIndex[11] = { 3, 6, 7 };
}

Shader3D::~Shader3D()
{
	delete[] pPos;
	delete[] cColor;
	delete[] iIndex;
}