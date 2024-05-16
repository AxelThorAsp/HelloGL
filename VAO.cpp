#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &_id);
}

VAO::~VAO()
{
	Delete();
}

void VAO::LinkVBO(const VBO& vbo, const VertexBufferLayout& layout)
{
	vbo.Bind();
	const auto& elements = layout.GetElememts();
	size_t offset = 0;
	for (GLuint i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride()
			,(const void *) offset);
		glEnableVertexAttribArray(i);

		// TODO: Handle other types
		offset += element.count * sizeof(GL_FLOAT);
	}
	vbo.Unbind();
}

void VAO::LinkVBO(VBO* vbo, GLuint layout, GLint numComponents, GLenum type, GLsizeiptr stride, size_t offset)
{
	(* vbo).Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, (void *) offset);
	glEnableVertexAttribArray(layout);
	(* vbo).Unbind();
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