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
#include "Rectangle.h"


#define WIN_H 600
#define WIN_W 600

const char *fragFilePath = "default.frag";
const char *vertFilePath = "default.vert";

int main(void)
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// use CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "HelloOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// v-sync
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

	Rectangle rect(1.0f, 1.0f, 0, 0);
	Rectangle rect1(0.5f, 0.5f, -0.5, -0.5);

	VAO vao;
	vao.Bind();

	VBO vbo(rect.GetVertices().data(), rect.GetVertices().size() * sizeof(GLfloat));
	EBO ebo(rect.GetIndices().data(), rect.GetIndices().size());
	VertexBufferLayout layout;

	layout.Push<GLfloat>(3);

	layout.Push<GLfloat>(3);

	vao.LinkVBO(vbo, layout);

	VAO vao1;
	vao1.Bind();
	VBO vbo1(rect1.GetVertices().data(), rect1.GetVertices().size() * sizeof(GLfloat));
	ebo.Bind();
	vao1.LinkVBO(vbo1, layout);

	/*
	vao.LinkVBO(&vbo, 0, sizeof(Pos) / sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
	vao.LinkVBO(&vbo, 1, sizeof(Color) / sizeof(GLfloat), GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
	*/

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
		vao1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
		vao1.Unbind();
		// Bind the VAO so OpenGL knows to use it
		vao.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
		vao.Unbind();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}