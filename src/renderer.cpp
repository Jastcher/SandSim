#include "renderer.h"
#include "shader.h"

Renderer::Renderer()
{
  glGenVertexArrays(1, &m_LonelyVao);
}

Renderer::~Renderer()
{
}

void Renderer::RenderScene()
{
  m_Shader.Activate();

  glBindVertexArray(m_LonelyVao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
