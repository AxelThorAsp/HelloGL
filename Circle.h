#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include <glad/glad.h>

class Circle
{

private:
	std::vector<GLfloat> m_Vertices;
	std::vector<GLuint> m_Indices;

public:
	Circle(GLfloat radius, GLfloat x, GLfloat y);

	inline const std::vector<GLfloat>& GetVertices() const
	{
		return m_Vertices;
	}

	inline const std::vector<GLuint>& GetIndices() const
	{
		return m_Indices;
	}
};

#endif // CIRCLE_H
