#include "simulator.h"
#include "computeShader.h"
#include "dataTexture.h"
#include <GL/gl.h>

Simulator::Simulator(int width, int height)
    : m_DataTexture(width, height), m_Width(width), m_Height(height)
{
  m_ComputeSim  = ComputeShader("../src/shaders/sim.comp");
  m_ComputeDraw = ComputeShader("../src/shaders/draw.comp");
}
Simulator::~Simulator()
{
}

void Simulator::Draw(int mouseX, int mouseY)
{
  m_ComputeDraw.Activate();
  glBindImageTexture(0, m_DataTexture.id, 0, GL_FALSE, 0, GL_READ_WRITE,
                     GL_RGBA8);
  m_ComputeDraw.SetVec2("u_MousePos", glm::vec2(mouseX, mouseY));
  m_ComputeDraw.SetInt("selection", selection);
  m_ComputeDraw.SetFloat("width", drawWidth);

  m_ComputeDraw.Dispatch(m_Width / 8, m_Height / 8);

  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void Simulator::Step()
{
  m_ComputeSim.Activate();
  glBindImageTexture(0, m_DataTexture.id, 0, GL_FALSE, 0, GL_READ_WRITE,
                     GL_RGBA8);

  m_ComputeSim.Dispatch(m_Width / 8, m_Height / 8);

  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}
void Simulator::Resize(int width, int height)
{
  m_DataTexture.Resize(width, height);
  m_Width  = width;
  m_Height = height;
}

GLuint Simulator::GetDataTextureID()
{
  return m_DataTexture.id;
}
