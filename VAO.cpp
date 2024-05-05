#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &_id);
}

VAO::~VAO()
{
	Delete();
}

void VAO::LinkVBO(VBO* vbo, GLuint layout)
{
	(*vbo).Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	(*vbo).Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(_id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &_id);
}