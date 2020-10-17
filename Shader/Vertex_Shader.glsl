#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;
out vec3 outColor;

void main()
{
	gl_Position = vec4(vPos, 0.1);
	outColor = vColor;
}