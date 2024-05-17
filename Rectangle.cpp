#include "Rectangle.h"


Rectangle::Rectangle(GLfloat width, GLfloat height, GLfloat x, GLfloat y)
{
	m_Indices.insert(m_Indices.end(), {0,1,2,0,3,2});

	// 1
	m_Vertices.push_back(x);
	m_Vertices.push_back(y);
	m_Vertices.push_back(0);

	// col
	m_Vertices.push_back(0);
	m_Vertices.push_back(0);
	m_Vertices.push_back(1);

	// 2
	m_Vertices.push_back(x + width);
	m_Vertices.push_back(y);
	m_Vertices.push_back(0);

	// col
	m_Vertices.push_back(0);
	m_Vertices.push_back(0);
	m_Vertices.push_back(1);

	// 3
	m_Vertices.push_back(x + width);
	m_Vertices.push_back(y + height);
	m_Vertices.push_back(0);

	// col
	m_Vertices.push_back(0);
	m_Vertices.push_back(0);
	m_Vertices.push_back(1);

	// 4
	m_Vertices.push_back(x);
	m_Vertices.push_back(y + height);
	m_Vertices.push_back(0);

	// col
	m_Vertices.push_back(0);
	m_Vertices.push_back(0);
	m_Vertices.push_back(1);
}
