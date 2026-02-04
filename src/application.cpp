#include "application.h"
#include "GLFW/glfw3.h"
#include "renderer.h"
#include "window.h"
#include <iostream>
#include <memory>

Application::Application()
{
  Init();
};

Application::~Application() {};

bool Application::Init()
{

  m_Window      = std::make_shared<Window>();
  m_Renderer    = std::make_shared<Renderer>(m_Window);
  m_FrameBuffer = std::make_shared<FrameBuffer>(m_Window->GetWidth(),
                                                m_Window->GetHeight());
  m_Simulator =
      std::make_shared<Simulator>(m_Window->GetWidth(), m_Window->GetHeight());
  m_UI = std::make_shared<UI>(m_FrameBuffer, m_Window, m_Simulator);

  return true;
}

void Application::Run()
{

  while (!glfwWindowShouldClose(m_Window->window))
    {

      if (m_UI->didViewportResize)
        {

          int viewportWidth  = m_UI->viewportSize.x;
          int viewportHeight = m_UI->viewportSize.y;
          std::cout << viewportWidth << " ; " << viewportHeight << std::endl;
          m_FrameBuffer->Resize(viewportWidth, viewportHeight);
          m_Simulator->Resize(viewportWidth, viewportHeight);

          m_UI->didViewportResize = false;
        }

      if (m_UI->isMouseDown)
        {
          m_Simulator->Draw(m_UI->viewportMouseX, m_UI->viewportMouseY);
        }

      for (int i = 0; i < 1; i++)
        {
          if (m_Simulator->isSimRunning) m_Simulator->Step();
        }

      m_FrameBuffer->Bind();

      m_Window->Clear();

      m_Renderer->RenderScene(m_Simulator->GetDataTextureID());

      m_FrameBuffer->Unbind();

      m_UI->Render();

      m_Window->Update();
    }
}
