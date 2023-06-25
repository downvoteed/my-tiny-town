#version 330 core
//vertex shader

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

int main()
{
	gl_Position = vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}
