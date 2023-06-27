#include "utils.hh"

glm::vec3 idToColor(int id) 
{
    int r = (id & 0x000000FF) >>  0;
    int g = (id & 0x0000FF00) >>  8;
    int b = (id & 0x00FF0000) >> 16;

    return glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}

int colorToId(const glm::vec3& color) 
{
    int r = static_cast<int>(color.r * 255);
    int g = static_cast<int>(color.g * 255);
    int b = static_cast<int>(color.b * 255);

    return ((r << 0) | (g << 8) | (b << 16)) / 255;
}
