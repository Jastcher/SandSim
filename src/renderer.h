#pragma once
#include "shader.h"
#include "window.h"
#include <memory>

class Renderer
{

public:
  Renderer(std::shared_ptr<Window> window);
  ~Renderer();
  void RenderScene(GLuint textureID);

private:
  Shader m_Shader;
  GLuint m_LonelyVao;

  std::shared_ptr<Window> m_Window;
};
