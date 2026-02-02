#include "dataTexture.h"

DataTexture::DataTexture(int width, int height)
{
  Init(width, height);
}

DataTexture::~DataTexture()
{

  glDeleteTextures(1, &id);
}

void DataTexture::Init(int width, int height)
{

  glCreateTextures(GL_TEXTURE_2D, 1, &id);
  // Allocate storage (RGBA32F is 4 floats per pixel)
  glTextureStorage2D(id, 1, GL_RGBA8, width, height);

  // Set parameters as usual
  glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  float clearColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glClearTexImage(id, 0, GL_RGBA, GL_FLOAT, clearColor);
}

void DataTexture::Resize(int width, int height)
{

  if (id != 0)
    {
      glDeleteTextures(1, &id);
    }
  Init(width, height);
}
