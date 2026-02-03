#pragma once

#include "computeShader.h"
#include "dataTexture.h"
#include <GL/gl.h>
class Simulator
{
public:
  Simulator(int width, int height);
  ~Simulator();

  void Draw(int mouseX, int mouseY);
  void Step();
  void Resize(int width, int height);
  GLuint GetDataTextureID();

  int selection   = 1;
  float drawWidth = 15.0f;

  bool isSimRunning = false;

private:
  ComputeShader m_ComputeSim;
  ComputeShader m_ComputeDraw;
  DataTexture m_DataTexture;

  int m_Width, m_Height;
};
