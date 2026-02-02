#pragma once
#include "window.h"
#include <memory>

class FrameBuffer
{
public:
  unsigned int id;
  unsigned int textureColorbuffer;
  unsigned int rbo;

  FrameBuffer(int width, int height);
  void Init(int width, int height);
  void Resize(int width, int height);

  void Bind();
  void Unbind();
};
