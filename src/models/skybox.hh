#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>
#include "vertex-buffer-layout.hh"
#include "vertex-array.hh"
#include "vertex-buffer.hh"
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb/stb_image.h""
#include "renderer/shader.hh"

class SkyboxSunset
{
public:
	SkyboxSunset(const std::string& cubemapPath)
	{
		std::vector<std::string> faces
		{
			"assets/textures/skyboxes/skybox_px.png", // Right
			"assets/textures/skyboxes/skybox_nx.png", // Left
			"assets/textures/skyboxes/skybox_py.png", // Top
			"assets/textures/skyboxes/skybox_ny.png", // Bottom
			"assets/textures/skyboxes/skybox_pz.png", // Back
			"assets/textures/skyboxes/skybox_nz.png", // Front
		};

		this->cubemapTexture_ = loadCubemap(faces);

		float skyboxVertices[] = {
			// Positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		this->skyboxShader_ = std::make_unique<Shader>("assets/shaders/skybox-vertex.glsl", "assets/shaders/skybox-fragment.glsl");

		this->vao_ = std::make_unique<VertexArray>();
		this->vao_->bind();
		this->vbo_ = std::make_unique<VertexBuffer>(skyboxVertices, sizeof(skyboxVertices));
		this->vbo_->bind();

		VertexBufferLayout layout;
		layout.push<float>(3);
		this->vao_->addBuffer(*this->vbo_, layout);

	}

	~SkyboxSunset()
	{
		glDeleteTextures(1, &cubemapTexture_);
	}

	void Draw()
	{
		glDepthMask(GL_FALSE);
		this->skyboxShader_->bind();

		// Create a new view matrix stripped of translation
		glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(this->view_));  // remove translation from the view matrix

		this->skyboxShader_->setUniformMat4f("view", viewNoTranslation);
		this->skyboxShader_->setUniformMat4f("projection", this->projection_);

		this->vao_->bind();
		this->vbo_->bind();
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture_);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);

		this->vao_->unbind();
		this->vbo_->unbind();

		this->skyboxShader_->unbind();
	}



	void setProjection(glm::mat4& projection)
	{
		this->projection_ = projection;
	}
	void setView(glm::mat4& view)
	{
		this->view_ = view;
	}

private:
	std::unique_ptr<VertexArray> vao_;
	std::unique_ptr<VertexBuffer> vbo_;
	std::unique_ptr<IndexBuffer> ibo_;
	std::unique_ptr<Shader> skyboxShader_;
	glm::mat4 view_;
	glm::mat4 projection_;
	GLuint cubemapTexture_;

	unsigned int loadCubemap(std::vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}

};
