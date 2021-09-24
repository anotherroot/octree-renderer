#include "vector"
struct GLFWwindow;
namespace arc {

typedef void (*UpdateFn)(double);


int Setup(int w, int h, const char *title = "Octree Renderer");
int Dispose();
int Run();
void Close();
void SetVsync(bool val);
void SetSize(int w, int h);
void SetResizeCallback(void fn(GLFWwindow* win, int w, int h));
void SetCloseCallback(void fn(GLFWwindow* win));

void SetUpdate(UpdateFn fn);
void SetImGuiUpdate(UpdateFn fn);



} // namespace arc
