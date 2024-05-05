#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{

private:
	GLuint _id;

public:
	VAO();
	~VAO();

	void LinkVBO(VBO* VBO, GLuint layout);

	void Bind();

	void Unbind();

	void Delete();
};

#endif // VAO_H
