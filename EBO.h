#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
* Element Buffer Object
* An Element Buffer Object (EBO) is a type of buffer object
* in OpenGL used to store indices that define geometric primitives (such as triangles) for rendering.
*/
class EBO
{

private:
	GLuint _id;

public:
	EBO(GLuint* indices, GLsizeiptr size);
	~EBO();

	// This tells OpenGL that subsequent vertex data operations should be applied to this buffer object.
	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	void Bind();

	void Unbind();

	void Delete();
};

#endif // VBO_H
