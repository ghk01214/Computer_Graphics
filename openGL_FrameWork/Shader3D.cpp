#include "Shader3D.h"

Shader3D::Shader3D(GLint k)
{
	this->pPos = new Pos[k];
	this->cColor = new Color[k];
	this->iIndex = new Index[2 * k - 4];
}

GLvoid Shader3D::InitializeBuffer()
{
	this->uiVAO = this->ReturnVAO();

	glBindVertexArray(this->uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, this->iVertexNum * sizeof(Pos), this->pPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->iIndexNum * sizeof(Index), this->iIndex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, this->uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, this->iVertexNum * sizeof(Color), this->cColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	this->InputVAO(this->uiVAO);
}

GLvoid Shader3D::Render()
{
	glUseProgram(this->ReturnShaderID());

	glBindVertexArray(this->uiVAO);
	glDrawElements(GL_TRIANGLES, this->iIndexNum * 3, GL_UNSIGNED_INT, 0);
}

GLvoid Shader3D::MakePolygon(GLint, Pos)
{
	return GLvoid();
}

GLvoid Shader3D::InitializeProgram()
{

}

Shader3D::~Shader3D()
{

}