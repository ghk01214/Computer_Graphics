#pragma once
#include "header.h"

typedef bool GLbool;

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

namespace Num
{
	enum Size
	{
		WINDOW_POS = 300, WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600, VBO = 2
	};

	enum Direction
	{
		RT = 100, LT, RB, LB
	};
}

namespace Manage
{
	enum Type
	{
		//선분, 삼각형, 사각형
		Line = 2, Triangle, Square
	};
}

namespace Transform
{
	enum Type
	{
		Translate, Rotate, Scale
	};
}