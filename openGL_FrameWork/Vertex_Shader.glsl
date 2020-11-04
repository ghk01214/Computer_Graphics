#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vInColor;

uniform mat4 mWorld;
uniform mat4 mView;
uniform mat4 mProjection;

out vec3 vOutColor;

void main()
{
	gl_Position = mProjection * mView * mWorld * vec4(vPos, 1.0f);
	vOutColor = vInColor;
}