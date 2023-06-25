#version 330 core
//fragment shader

in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D textureSampler;

void main()
{
    // Sample the color from the texture
    color = texture(textureSampler, TexCoord);
}
