#pragma once
#include "header.h"

struct Pos
{
	GLfloat X, Y, Z;
};

struct Color
{
	GLfloat R, G, B;
};

struct Index
{
	GLuint V1, V2, V3;
};

struct Angle
{
	GLfloat X, Y, Z;
};

struct RotateMat
{
	glm::mat4 X, Y, Z;
};

namespace NUM
{
	enum Size
	{
		WINDOW_POS = 300, WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600, VBO = 2
	};
}

namespace Manage
{
	enum Type
	{
		//점, 선, 삼각형, 사각형, 정사면체, 사각뿔, 정육면체, 구
		Line, Triangle, Square, Circle, Tetrahedron, Pyramid, Cone, Cube, Sphere
	};
}