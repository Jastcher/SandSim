#pragma once

#include "computeShader.h"
#include "dataTexture.h"
#include <GL/gl.h>

struct Particle
{
  const char *name;
  unsigned char id;
  unsigned char props;
  unsigned char states;
};

enum Properties : unsigned char
{
  SOLID  = 1,
  LIQUID = 1 << 1,
  GRAIN  = 1 << 2,
};

class Simulator
{
public:
  Simulator(int width, int height);
  ~Simulator();

  void Draw(int mouseX, int mouseY);
  void Step();
  void Resize(int width, int height);
  GLuint GetDataTextureID();

  float drawRadius = 15.0f;

  bool isSimRunning = false;

  int selection = 0;

  std::vector<Particle> particles;

private:
  ComputeShader m_ComputeSim;
  ComputeShader m_ComputeDraw;

  DataTexture m_DataTexture;
  DataTexture m_DataTextureNext;

  int m_Width, m_Height;
};
