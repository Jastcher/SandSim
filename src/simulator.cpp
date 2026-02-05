#include "simulator.h"
#include "computeShader.h"
#include "dataTexture.h"
#include <GL/gl.h>

Simulator::Simulator(int width, int height)
    : m_DataTexture(width, height), m_DataTextureNext(width, height),
      m_Width(width), m_Height(height)
{
  m_ComputeSim  = ComputeShader("../src/shaders/sim.comp");
  m_ComputeDraw = ComputeShader("../src/shaders/draw.comp");

  particles = {{"Air", 0, 0, 0},
               {"Sand", 1, SOLID | GRAIN, 1},
               {"Stone", 2, SOLID, 0},
               {"Water", 3, LIQUID | GRAIN, 1}};
}

Simulator::~Simulator()
{
}

void Simulator::Draw(int mouseX, int mouseY)
{
  m_ComputeDraw.Activate();
  glBindImageTexture(0, m_DataTexture.id, 0, GL_FALSE, 0, GL_READ_WRITE,
                     GL_RGBA8UI);
  Particle p = particles[selection];
  m_ComputeDraw.SetVec2("u_MousePos", glm::vec2(mouseX, mouseY));

  m_ComputeDraw.SetInt("id", p.id);
  m_ComputeDraw.SetInt("props", p.props);
  m_ComputeDraw.SetInt("states", p.states);

  m_ComputeDraw.SetFloat("radius", drawRadius);

  m_ComputeDraw.Dispatch(m_Width / 8, m_Height / 8);

  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void Simulator::Step()
{
  m_ComputeSim.Activate();
  glBindImageTexture(0, m_DataTexture.id, 0, GL_FALSE, 0, GL_READ_WRITE,
                     GL_RGBA8UI);
  glBindImageTexture(1, m_DataTextureNext.id, 0, GL_FALSE, 0, GL_READ_WRITE,
                     GL_RGBA8UI);

  m_ComputeSim.Dispatch(m_Width / 8, m_Height / 8);

  glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

  GLuint temp          = m_DataTexture.id;
  m_DataTexture.id     = m_DataTextureNext.id;
  m_DataTextureNext.id = temp;
}
void Simulator::Resize(int width, int height)
{
  m_DataTexture.Resize(width, height);
  m_DataTextureNext.Resize(width, height);
  m_Width  = width;
  m_Height = height;
}

GLuint Simulator::GetDataTextureID()
{
  return m_DataTexture.id;
}
