#version 330 core

out vec4 vFragmentColor;
in vec3 vOutColor;

void main()
{
	vFragmentColor = vec4(vOutColor, 1.0);
}