#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"


#define WIN_H 800
#define WIN_W 800

const char* fragFilePath = "default.frag";
const char* vertFilePath = "default.vert";

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

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	Shader shader = Shader(vertFilePath, fragFilePath);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f,   -0.5f  * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f,  -0.5f    * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f      * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f  / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f     * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLfloat colors[] =
	{
		0.6f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.5f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 1.0f,
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 5
	};


	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	VBO vbocol(colors, sizeof(colors));

	EBO ebo(indices, sizeof(indices));

	vao.LinkVBO(&vbo, 0);
	vao.LinkVBO(&vbocol, 1);

	vbo.Unbind();
	vao.Unbind();
	ebo.Unbind();

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shader.Activate();
		// Bind the VAO so OpenGL knows to use it
		vao.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
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