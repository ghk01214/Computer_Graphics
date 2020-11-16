#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vInColor;

out vec3 vOutColor;

void main()
{
	gl_Position = vec4(vPos, 1.0f);
	vOutColor = vInColor;
}