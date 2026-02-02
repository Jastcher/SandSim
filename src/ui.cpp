#include "ui.h"
#include <memory>
#include "imgui/imgui.h"
static inline void StartFrame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

static inline void RenderUI()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UI::UI(std::shared_ptr<FrameBuffer> _frameBuffer,
       std::shared_ptr<Window> _window)
    : frameBuffer(_frameBuffer), window(_window)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

  ImGui_ImplGlfw_InitForOpenGL(window->window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

UI::~UI()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

static inline void MainWindow()
{
  ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
  ImGuiWindowFlags host_window_flags = 0;
  host_window_flags |= ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
  host_window_flags |=
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

  ImGui::Begin("MainWindow", nullptr, host_window_flags);
  ImGui::PopStyleVar(3);
  ImGuiID dockspace_id = ImGui::GetID("DockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags, nullptr);
  ImGui::End();
}

static inline void ViewportWindow(UI *UI)
{
  ImGui::Begin("Viewport");
  float viewportWidth  = ImGui::GetWindowWidth();
  float viewportHeight = ImGui::GetWindowHeight();

  // Swap the y-coordinates in the ImVec2 to avoid rendering the framebuffer
  // upside down
  ImGui::GetWindowDrawList()->AddImage(
      (unsigned int *)UI->frameBuffer->textureColorbuffer,
      ImVec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y),
      ImVec2(ImGui::GetCursorScreenPos().x + viewportWidth,
             ImGui::GetCursorScreenPos().y + viewportHeight),

      ImVec2(0, 1), ImVec2(1, 0));

  UI->viewportFocused = ImGui::IsWindowHovered();

  ImVec2 mousePos = ImGui::GetMousePos();
  UI->viewportMouseX =
      mousePos.x - ImGui::GetCursorScreenPos().x - ImGui::GetScrollX();
  UI->viewportMouseY =
      mousePos.y - ImGui::GetCursorScreenPos().y - ImGui::GetScrollY();

  ImGui::End();
}

void UI::Render()
{
  StartFrame();

  ImGui::SetNextWindowSize(ImVec2(window->GetWidth(), window->GetHeight()));
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  // ImGui::ShowDemoWindow();

  MainWindow();
  ViewportWindow(this);

  RenderUI();
}
