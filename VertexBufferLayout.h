#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H
#include <vector>
#include <glad/glad.h>

struct VertexBufferElement
{
	GLuint count;
	GLenum type;
	bool normalized;
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;
public:
	VertexBufferLayout() : m_Stride(0)
	{}


	template<typename T>
	void Push(unsigned int count);

	template<>
	void Push<GLfloat>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += (sizeof(GLfloat) * count);
	}

	template<>
	void Push<GLuint>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += (sizeof(GLuint) * count);
	}

	inline const std::vector<VertexBufferElement> GetElememts() const& { return m_Elements; }

	inline GLuint GetStride() const { return m_Stride; }
};

#endif // VERTEX_BUFFER_LAYOUT_H
