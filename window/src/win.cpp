#include "../include/win.hpp"
#include "../../ext/glad/include/glad/glad.h"
#include "../../ext/glfw/include/GLFW/glfw3.h"
#include "../../ext/imgui/backends/imgui_impl_glfw.h"
#include "../../ext/imgui/backends/imgui_impl_opengl3.h"
#include "../../ext/imgui/imgui.h"

#include "assert.h"
#include "map"
#include "stdio.h"
namespace arc {
// structs
struct Window {
  void *win{nullptr};
  const char *title;
  int w;
  int h;
  bool running;
  bool vsync{false};

  UpdateFn update_imgui_fn{nullptr};
  UpdateFn update_game_fn{nullptr};
};

// declarations
void ImGuiSetup();
void ImGuiDispose();

// variables
Window win;
double last_frame_time;
double delta_time;

static bool s_glfw_initialized = false;
static void GLFWErrorCallback(int error, const char *message) {
  fprintf(stderr, "GLFW Error (%d): %s\n", error, message);
}
int Setup(int w, int h, const char *title) {
  if (win.win) {
    fprintf(stderr, "Window Setup failed: window already exists");
    return 1;
  }
  /* assert(win.id!=nullptr, "Window Setup failed! Window already exists"); */

  win.title = title;
  win.w = w;
  win.h = h;

  /* logci("Creating window {0} ({1}, {2})", props.title, props.width, */
  /*       props.height); */

  if (!s_glfw_initialized) {
    // TODO: glfwterminate on system shutdown
    int success = glfwInit();
    /* arc_core_assert(success, "Could not initialize GLFW!"); */
    glfwSetErrorCallback(GLFWErrorCallback);

    s_glfw_initialized = true;
  }
  win.win = glfwCreateWindow(win.w, win.h, win.title, nullptr, nullptr);

  glfwMakeContextCurrent((GLFWwindow *)win.win);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  if (!status) {
    fprintf(stderr, "Failed to initialize Glad!");
    return 1;
  }

  printf("OpenGL Info:\n");
  printf("  Vendor: %s,\n", glGetString(GL_VENDOR));
  printf("  Renderer: %s,\n", glGetString(GL_RENDERER));
  printf("  Version: %s,\n", glGetString(GL_VERSION));

  SetVsync(true);

  /* glfwSetCharCallback((GLFWwindow *)win.win, */
  /*                     [](GLFWwindow *window, unsigned int key_code) {}); */
  /* glfwSetKeyCallback( */
  /*     (GLFWwindow *)win.win, */
  /*     [](GLFWwindow *window, int key, int scan_code, int action, int mods)
   * {}); */
  /* glfwSetMouseButtonCallback( */
  /*     (GLFWwindow *)win.win, */
  /*     [](GLFWwindow *window, int button, int action, int mods) {}); */
  /* glfwSetScrollCallback( */
  /*     (GLFWwindow *)win.win, */
  /*     [](GLFWwindow *window, double x_offset, double y_offset) {}); */
  /* glfwSetCursorPosCallback( */
  /*     (GLFWwindow *)win.win, */
  /*     [](GLFWwindow *window, double x_pos, double y_pos) {}); */
  ImGuiSetup();
  return 0;
}
int Dispose() {
  if (win.win) {
    glfwDestroyWindow((GLFWwindow *)win.win);
    win.win = nullptr;
    ImGuiDispose();
    return 0;
  }
  return 1;
}
void SetResizeCallback(void fn(GLFWwindow *win, int w, int h)) {
  glfwSetWindowSizeCallback((GLFWwindow *)win.win, fn);
}
void SetCloseCallback(void fn(GLFWwindow *win)) {
  glfwSetWindowCloseCallback((GLFWwindow *)win.win, fn);
}
void SetVsync(bool val) {
  assert(s_glfw_initialized);
  if (val) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  win.vsync = val;
}
void SetSize(int w, int h) { glfwSetWindowSize((GLFWwindow *)win.win, w, h); }

void ImGuiSetup() {
  bool err = gladLoadGL() == 0;
  if (err) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    return;
  } else {
    printf("dela :(\n");
  }
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard
  // Controls
  io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;

  // io.Fonts->AddFontFromFileTTF("/home/adolin/CLionProjects/arc_engine/test_core/assets/roboto_font/Roboto-Medium.ttf",
  // 18.0f); io.FontDefault =
  // io.Fonts->AddFontFromFileTTF("/home/adolin/CLionProjects/arc_engine/test_core/assets/roboto_font/Roboto-Medium.ttf",
  // 18.0f);

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform
  // windows can look identical to regular ones.
  ImGuiStyle &style = ImGui::GetStyle();

  // SetDarkThemeColors();

  GLFWwindow *window = static_cast<GLFWwindow *>(win.win);
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");

  // Setup Platform/Renderer bindings
}

void ImGuiDispose() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

int Run() {
  win.running = true;
  if (win.update_game_fn == nullptr || win.update_imgui_fn == nullptr) {
    fprintf(stderr,
            "Run error: game update fn and imgui update fn must be set\n");
    return 1;
  }
  last_frame_time = glfwGetTime();
  while (win.running) {
    double time = glfwGetTime();
    delta_time = time - last_frame_time;
    last_frame_time = time;

    glfwPollEvents();
    // game
    win.update_game_fn(delta_time);
    // ImGUI
    {
      // begin
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      win.update_imgui_fn(delta_time);
      // end
      ImGuiIO &io = ImGui::GetIO();
      io.DisplaySize = ImVec2((float)win.w, (float)win.h);
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    glfwSwapBuffers((GLFWwindow *)win.win);
  }
  return 0;
}
void Close() {
  win.running = false;
  printf("closed\n");
}
void SetUpdate(UpdateFn fn) { win.update_game_fn = fn; }
void SetImGuiUpdate(UpdateFn fn) { win.update_imgui_fn = fn; }
} // namespace arc
