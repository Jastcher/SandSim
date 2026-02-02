#pragma once
#include "frameBuffer.h"
#include "window.h"
#include <memory>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class UI
{
public:
  UI(std::shared_ptr<FrameBuffer> frameBuffer, std::shared_ptr<Window> window);
  ~UI();

  void Render();

public:
  bool viewportFocused;

  // viewport mouse coords
  int viewportMouseX, viewportMouseY;

  std::shared_ptr<FrameBuffer> frameBuffer;
  std::shared_ptr<Window> window;
};
