#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
* Vertex Buffer Object 
* Provides methods for uploading vertex data (position, normal vector, color, etc.)
* to the video device for non-immediate-mode rendering. 
*/
class VBO
{

private:
	GLuint _id;

public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	~VBO();

	// This tells OpenGL that subsequent vertex data operations should be applied to this buffer object.
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	void Bind();

	void Unbind();

	void Delete();

	void Update(GLsizeiptr size, GLfloat* vertices);

};

#endif // VBO_H
