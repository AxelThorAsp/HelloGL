#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"
#include "VertexBufferLayout.h"

class VAO
{

private:
	GLuint _id;

public:
	VAO();
	~VAO();

	void LinkVBO(const VBO& vbo, const VertexBufferLayout& layout);
	
	void LinkVBO(VBO* vbo, GLuint layout, GLint numComponents, GLenum type, GLsizeiptr stride, size_t offset);

	void Bind();

	void Unbind();

	void Delete();
};

#endif // VAO_H
