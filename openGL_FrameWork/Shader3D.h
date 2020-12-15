#pragma once
#include "BaseShader.h"

class Shader3D : public BaseShader
{
public:
	Shader3D();
	~Shader3D();
public:
	virtual GLvoid CreateObject(GLint iType) override;
	virtual GLvoid CreateObject(GLint iType, glm::vec3 color) override;
};