#version 330 core
//fragment shader

in vec2 TexCoord;

uniform vec3 objectColor;
uniform bool isPicking;
out vec4 color;

uniform sampler2D textureSampler;

void main()
{
    if (isPicking)
        color = vec4(objectColor, 1.0);
    else
		color = texture(textureSampler, TexCoord);

}
