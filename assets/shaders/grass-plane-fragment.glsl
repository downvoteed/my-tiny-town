#version 330 core

in vec2 TexCoord;
in vec3 FragPos;

out vec4 color;

uniform sampler2D diffTexture;
uniform sampler2D armTexture;

void main()
{
    vec3 diffColor = texture(diffTexture, TexCoord).rgb;
    float ao = texture(armTexture, TexCoord).r;
    float roughness = texture(armTexture, TexCoord).g;
    float metallic = texture(armTexture, TexCoord).b;

    vec3 finalColor = ao * diffColor;

    color = vec4(finalColor, 1.0);
}
