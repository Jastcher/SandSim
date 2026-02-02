#pragma once
#include "shader.h"

class Renderer
{

public:
  Renderer();
  ~Renderer();
  void RenderScene();

private:
  Shader m_Shader = Shader("../src/shaders/default.shader");
  GLuint m_LonelyVao;
};
