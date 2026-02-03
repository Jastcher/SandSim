#include "renderer.h"
#include "computeShader.h"
#include "shader.h"
#include <memory>

Renderer::Renderer(std::shared_ptr<Window> window) : m_Window(window)
{
  glGenVertexArrays(1, &m_LonelyVao);

  m_Shader = Shader("../src/shaders/default.shader");
}

Renderer::~Renderer()
{
}

void Renderer::RenderScene(GLuint textureID)
{
  m_Shader.Activate();
  m_Shader.SetInt("width", m_Window->GetWidth());
  m_Shader.SetInt("height", m_Window->GetHeight());

  glBindImageTexture(0, textureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);

  glBindVertexArray(m_LonelyVao);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  // glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}
