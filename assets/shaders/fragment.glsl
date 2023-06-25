#version 330 core
//fragment shader

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

int main()
{
	color = vec4(ourColor, 1.0f);
}
