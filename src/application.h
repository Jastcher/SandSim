#pragma once
#include "window.h"
#include "renderer.h"
#include "frameBuffer.h"
#include "ui.h"
#include "dataTexture.h"

#include <memory>
class Application
{
public:
  Application();
  ~Application();

  void Run();

  bool Init();

private:
  bool m_Running = false;

  std::shared_ptr<Window> m_Window;
  std::shared_ptr<Renderer> m_Renderer;
  std::shared_ptr<FrameBuffer> m_FrameBuffer;
  std::shared_ptr<UI> m_UI;
  std::shared_ptr<DataTexture> m_DataTexture;

  GLuint dataTexture;
};
