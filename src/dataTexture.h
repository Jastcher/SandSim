#pragma once
#include "window.h"

#include <GL/gl.h>
class DataTexture
{
public:
  DataTexture(int width, int height);
  ~DataTexture();

  GLuint id;

  void Init(int width, int height);
  void Resize(int width, int height);
};
