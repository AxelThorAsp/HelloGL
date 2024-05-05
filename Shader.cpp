#include "Shader.h"


Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexShaderSource = read_file(vertexFile);
	std::string fragmentShaderSource = read_file(fragmentFile);

	auto v = vertexShaderSource.c_str();
	auto f = fragmentShaderSource.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &v, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &f, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	_id = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(_id, vertexShader);
	glAttachShader(_id, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(_id);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
Shader::~Shader()
{
	Delete();
}

GLuint Shader::GetId()
{
	return _id;
}

void Shader::Activate()
{
	glUseProgram(_id);

}

void Shader::Delete()
{
	glDeleteProgram(_id);
}

std::string Shader::read_file(const char* filepath)
{

	std::ifstream file(filepath);

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filepath << std::endl;
		throw(errno);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}
