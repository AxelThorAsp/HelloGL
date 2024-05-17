#include "Circle.h"
#include <math.h>



Circle::Circle(GLfloat radius, GLfloat x, GLfloat y)
{

	const float PI = 3.141592f;

	m_Vertices.push_back(x);
	m_Vertices.push_back(y);
	m_Vertices.push_back(0);

	m_Vertices.push_back(sinf(x));
	m_Vertices.push_back(cosf(y));
	m_Vertices.push_back(0);


	// 0 1 2
	// 0 2 3
	// 0 3 4

	int n = 25;
	int c = 1;

	for (GLuint ii = 1; ii < n; ii++)
	{
		m_Indices.push_back(0);
		m_Indices.push_back(ii);
		m_Indices.push_back(ii+1);
	}
	m_Indices.push_back(0);
	m_Indices.push_back(n);
	m_Indices.push_back(1);

	for (float i = 0; i < 2 * PI; i += 2 * PI / n)
	{
		m_Vertices.push_back(x + sinf(i) * radius);
		m_Vertices.push_back(y + cosf(i) * radius);
		m_Vertices.push_back(0);

		m_Vertices.push_back(sinf(i));
		m_Vertices.push_back(cosf(i));
		m_Vertices.push_back(0.3f);
	}
}