#pragma once
#include <string>
#include "glm/matrix.hpp"
#include <unordered_map>


class Shader
{
public:
	// rule of five
	/**
	 * @brief Creates a shader program from the given vertex and fragment shader files.
	 */
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	Shader(const Shader& other) = delete;
	Shader(Shader&& other) noexcept = delete;
	Shader& operator=(const Shader& other) = delete;
	Shader& operator=(Shader&& other) noexcept = delete;
	~Shader();

	/**
	 * @brief Binds the shader program.
	 */
	void bind() const;
	/**
	 * @brief Unbinds the shader program.
	 */
	void unbind() const;
	/**
	 * @brief Sets the int uniform with the given name to the given value.
	 */
	void setUniform1i(const std::string& name, int value);
	/**
	 * @brief Sets the float uniform with the given name to the given value.
	 */
	void setUniform1f(const std::string& name, float value);
	/**
	 * @brief Sets the vec3 uniform with the given name to the given values.
	 */
	void setUniform3f(const std::string& name, float v0, float v1, float v2);
	/**
	 * @brief Sets the vec4 uniform with the given name to the given values.
	 */
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	/**
	 * @brief Sets the mat4 uniform with the given name to the given matrix.
	 */
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	/**
	 * @brief Reads the shader file and returns the contents as a string.
	 * @param filepath The path to the shader file.
	 */
	std::string loadShader(const std::string& filepath);
	/**
	 * @brief the shader and returns the ID.
	 * @param type The type of shader to compile
	 * Must be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
	 */
	unsigned int compileShader(unsigned int type, const std::string& source);
	/**
	 * @brief Creates a shader program from the given vertex and fragment shader files.
	 * @param vertexShader The path to the vertex shader file.
	 * @param fragmentShader The path to the fragment shader file.
	 */
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	/**
	 * @brief Returns the location of the uniform with the given name.
	 */
	int getUniformLocation(const std::string& name);

	/**
	 * @brief The ID of the shader program.
	 */
	unsigned int programID;
	/**
	 * @brief A map of uniform names to their locations.
	 */
	std::unordered_map<std::string, int> UniformLocations;
};
