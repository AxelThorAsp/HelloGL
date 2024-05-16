#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Util.h"
#include "VertexBufferLayout.h"


#define WIN_H 600
#define WIN_W 600

const char *fragFilePath = "default.frag";
const char *vertFilePath = "default.vert";

struct Pos
{
	GLfloat x, y, z;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	Pos position;
	Color color;
};


int main(void)
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "HelloOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//Load GLAD so it configures OpenGL
	if (gladLoadGL() < 1)
	{
		std::cerr << "Error in gladLoadGL()" << std::endl;
		throw(errno);
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, WIN_W, WIN_H);

	Shader shader = Shader(vertFilePath, fragFilePath);

	const int NUM_VERT = 4;
	// Vertices coordinates
	Vertex vertices[] =
	{
		{
			{-0.5f, 0.0f, 0.0f},
			{0.4f, 0.3f, 0.52f}
		},
		{
			{ 0.5f, 0.0f, 0.0f},
			{0.3f, 0.3f, 0.42f}
		},
		{
			{ 0.5f, 1.0f, 0.0f},
			{0.2f, 0.2f, 0.8f}
		},
		{
			{-0.5f, 1.0f, 0.0f},
			{0.2f, 0.2f, 0.8f}
		},
	};


	const unsigned int NUM_IND = 6;
	// Indices for vertices order
	GLuint indices[NUM_IND] =
	{
		0, 1, 2,
		0, 3, 2
	};

	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(Vertex) * NUM_VERT);


	EBO ebo(indices, NUM_IND);

	VertexBufferLayout layout;

	layout.Push<GLfloat>(3);

	layout.Push<GLfloat>(3);

	vao.LinkVBO(vbo, layout);

	/*
	vao.LinkVBO(&vbo, 0, sizeof(Pos) / sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
	vao.LinkVBO(&vbo, 1, sizeof(Color) / sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
	*/

	vbo.Unbind();
	vao.Unbind();
	ebo.Unbind();

	// Gets ID of uniform called "u_Opac"
	GLuint uniID = glGetUniformLocation(shader.GetId(), "u_Red");


	// Main while loop
	float r = 0.0f;
	float dr = 0.01f;
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shader.Activate();
		glUniform1f(uniID, r);
		// Bind the VAO so OpenGL knows to use it
		vao.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
		vao.Unbind();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
		/*
		if (r > 1.0f)
			dr *= -1;
		if (r < 0.0f)
			dr *= -1;
		r += dr;
		*/
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}