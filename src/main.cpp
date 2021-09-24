/* standard libraries */
#include "stdio.h"

/* external libraries */
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
/* project libraries */
#include "win.hpp"


using namespace arc;

float backgorund[3];

void OnWindowResize(int w, int h) { glViewport(0, 0, w, h); }
void OnWindowClose() { Close(); }

void ImGuiUpdate(double delta_time) {
  ImGui::Begin("Options");
  ImGui::ColorEdit3("Color", backgorund);
  ImGui::End();
}

void Start() { backgorund[0] = 1; }

void Update(double delta_time) {
  printf("%lf\n", delta_time);
  glClearColor(backgorund[0], backgorund[1], backgorund[2], 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main() {
  Setup(256, 256);

  SetResizeCallback(OnWindowResize);
  SetCloseCallback(OnWindowClose);

  SetUpdate(&Update);
  SetImGuiUpdate(&ImGuiUpdate);

  Start();
  Run();

  Dispose();
  return 0;
}
