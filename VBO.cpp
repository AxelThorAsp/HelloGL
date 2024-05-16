#include "VBO.h"

VBO::VBO(const GLvoid *vertices, GLsizeiptr size)
{
	glGenBuffers(1, &m_id);

	Bind();

	Update(size, vertices);
}

VBO::~VBO()
{
	Delete();
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &m_id);
}

void VBO::Update(GLsizeiptr size, const GLvoid *vertices)
{
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
