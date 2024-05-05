#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &_id);

	Bind();

	Update(size, vertices);
}

VBO::~VBO()
{
	Delete();
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &_id);
}

void VBO::Update(GLsizeiptr size, GLfloat* vertices)
{
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
