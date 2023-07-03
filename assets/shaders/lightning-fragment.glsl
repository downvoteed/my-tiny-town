#version 330 core

in vec2 TexCoord;
in vec3 Normal; 
in vec3 FragPos; 

uniform vec3 objectColor;
uniform bool isPicking;
uniform sampler2D textureSampler;

uniform vec3 lightPos; 

out vec4 color;

void main()
{
    if (isPicking)
    {
        color = vec4(objectColor, 1.0);
    }
    else
    {
        // Ambient light
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0); 

        // Diffuse light
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(1.0, 1.0, 1.0); 

        // Combine lighting effects with the texture
        vec3 result = (ambient + diffuse) * vec3(texture(textureSampler, TexCoord));
        color = vec4(result, 1.0);
    }
}
