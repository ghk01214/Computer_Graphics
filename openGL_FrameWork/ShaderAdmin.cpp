#include "ShaderAdmin.h"

ShaderAdmin::ShaderAdmin()
{

}

GLvoid ShaderAdmin::MakeShader(GLint k, Pos pPos)
{
	switch (k)
	{
	case Manage::Line:
	{

		break;
	}
	case Manage::Triangle:
	{
		bShader = new Shader2D(3);

		break;
	}
	case Manage::Square:
	{
		bShader = new Shader2D(4);

		break;
	}
	case Manage::Circle:
	{

		break;
	}
	case Manage::Tetrahedron:
	{
		bShader = new Shader3D(4);
		
		break;
	}
	case Manage::Pyramid:
	{
		bShader = new Shader3D(5);

		break;
	}
	case Manage::Cone:
	{
		bShader = new Shader3D(17);

		break;
	}
	case Manage::Cube:
	{
		bShader = new Shader3D(8);

		break;
	}
	case Manage::Sphere:
	{
		bShader = new Shader3D(162);

		break;
	}
	default:
		break;
	}

	vList.push_back(std::make_pair(bShader, std::make_pair(k, pPos)));
}

GLvoid ShaderAdmin::Render()
{
	for (GLint i = 0; i < vList.size(); ++i)
	{
		vList[i].first->MakePolygon(vList[i].second.first, vList[i].second.second);
	}
}

ShaderAdmin::~ShaderAdmin()
{
	if (bShader != nullptr)
		delete bShader;
}