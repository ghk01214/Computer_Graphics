#pragma once
#include "header.h"

struct Pos
{
	GLfloat fX, fY, fZ;
};

struct Color
{
	GLfloat fR, fG, fB;
};

struct Index
{
	GLuint uiV1, uiV2, uiV3;
};

struct Angle
{
	GLfloat fX, fY, fZ;
};

struct RotateMat
{
	glm::mat4 mX, mY, mZ;
};
