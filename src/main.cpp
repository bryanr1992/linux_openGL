#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Build: cmake -B build && cmake --build build building command to remember

static void glfwErrorCallback(int error, const char* description){
  std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

int main() {
  glfwSetErrorCallback(glfwErrorCallback);

  // GLEW queries GLX directly and doesn't understant native Wayland/EGL 
  // contexts, so force the X11 (XWayland) backend
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
  
  GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
