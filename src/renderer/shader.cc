#include "shader.hh"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include "glad/glad.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) 
{
    std::string vertexShader = loadShader(vertexShaderPath);
    std::string fragmentShader = loadShader(fragmentShaderPath);
    this->programID = createShader(vertexShader, fragmentShader);
}

Shader::~Shader() 
{
    glDeleteProgram(this->programID);
}

void Shader::bind() const
{
    glUseProgram(this->programID);
}

void Shader::unbind() const 
{
    glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(getUniformLocation(name), v0, v1, v2);
}
void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

std::string Shader::loadShader(const std::string& filepath) 
{
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss;
    while (getline(stream, line))
        ss << line << '\n';

    return ss.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) 
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) 
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[512] = { 0 };
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
	GLint success;
	glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
   GLenum err;
   while((err = glGetError()) != GL_NO_ERROR)
   {
       std::cout << "error: " << err << std::endl;
   }

    glValidateProgram(program);
    glGetProgramiv(this->programID, GL_VALIDATE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
    


    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int Shader::getUniformLocation(const std::string& name) 
{
    if (this->UniformLocations.find(name) != this->UniformLocations.end())
        return this->UniformLocations[name];

    int location = glGetUniformLocation(this->programID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    else
        this->UniformLocations[name] = location;

    return location;
}
