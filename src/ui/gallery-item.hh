#pragma once
#include <functional>

struct GalleryItem
{
    GLuint texture;
    std::function<Model*(float x, float y)> createModel;
};
