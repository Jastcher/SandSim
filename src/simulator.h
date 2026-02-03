#pragma once

#include "computeShader.h"
#include "dataTexture.h"
#include <GL/gl.h>
class Simulator
{
public:
  Simulator(int width, int height);
  ~Simulator();

  void Step();
  void Resize(int width, int height);
  GLuint GetDataTextureID();

private:
  ComputeShader m_ComputeShader;
  DataTexture m_DataTexture;

  int m_Width, m_Height;
};
