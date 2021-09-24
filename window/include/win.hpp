struct GLFWwindow;
namespace arc {

typedef void (*UpdateFn)(double);
typedef void (*CloseFn)();
typedef void (*ResizeFn)(int, int);
typedef void (*KeyPressFn)(int, int);


int Setup(int w, int h, const char *title = "Octree Renderer");
int Dispose();
int Run();
void Close();
void SetVsync(bool val);
void SetSize(int w, int h);
void SetCloseCallback(CloseFn fn);
void SetResizeCallback(ResizeFn fn);

void SetUpdate(UpdateFn fn);
void SetImGuiUpdate(UpdateFn fn);



} // namespace arc
