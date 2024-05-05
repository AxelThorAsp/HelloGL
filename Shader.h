#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <iostream>

class Shader
{

private:
	std::string read_file(const char* filepath);
	GLuint _id;

public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	GLuint GetId();
	void Activate();
	void Delete();

};


#endif // SHADER_H
