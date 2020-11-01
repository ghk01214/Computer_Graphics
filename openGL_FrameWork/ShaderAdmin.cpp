#include "ShaderAdmin.h"

ShaderAdmin::ShaderAdmin()
{

}

GLvoid ShaderAdmin::MakeShader(GLint k)
{
	BaseShader* bShader;
	Pos pTemp = { 0.0f, 0.0f, 0.0f };

	switch (k)
	{
	case Manage::Line:
	{

		break;
	}
	case Manage::Triangle:
	{
		bShader = new Shader2D(3);
		bShader->MakePolygon(3, pTemp);

		break;
	}
	case Manage::Square:
	{
		bShader = new Shader2D(4);
		bShader->MakePolygon(4, pTemp);

		break;
	}
	case Manage::Circle:
	{

		break;
	}
	//case Manage::Tetrahedron:
	//{
	//	bShader = new Shader3D(4);
	//	break;
	//}
	//case Manage::Pyramid:
	//{
	//	bShader = new Shader3D(5);
	//	break;
	//}
	//case Manage::Hexahedron:
	//{
	//	bShader = new Shader3D(8);
	//	break;
	//}
	case Manage::Sphere:
	{

		break;
	}
	default:
		break;
	}

	delete bShader;
}

ShaderAdmin::~ShaderAdmin()
{

}