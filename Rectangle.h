#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <glad/glad.h>

class Rectangle
{

private:
	std::vector<GLfloat> m_Vertices;
	std::vector<GLuint> m_Indices;

public:
	Rectangle(GLfloat width, GLfloat height, GLfloat x, GLfloat y);

	inline const std::vector<GLfloat>& GetVertices() const
	{
		return m_Vertices;
	}

	inline const std::vector<GLuint>& GetIndices() const
	{
		return m_Indices;
	}
};

#endif // RECTANGLE_H
