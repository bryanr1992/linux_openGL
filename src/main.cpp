#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

// Build: cmake -B build && cmake --build build building command to remember

static void glfwErrorCallback(int error, const char* description){
  std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

int main(int argc, char* argv[]) {
    /*spin up seperate terminal to emulate vs behavior*/
    if(argc == 1){
        std::string command = "foot -e " + std::string(argv[0]) + " --run";
        std::system(command.c_str());        
        return 0;
    }
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
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        std::cout << "error" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    float positions[6] = {
        -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f,  -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    /*
     * Need to tell the OpenGL buffer what the data is about (What the layout of our data is)
     * in this context it is a triangle. We do this exactly
     * after the buffer has been bound.
     *
     * stride attr: This is the amount of bytes between each vertex.
     * The amount that we need to go forward to reach the next vertex.
     * */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*) 0);
    glEnableVertexAttribArray(0); //use the index for our vertex array that we want to enable
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);//use this to draw triangles without index buffer

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    std::cout << "Hello from a separate Linux terminal window!" << std::endl;
    std::cout << "\nPress Enter to close...";
    std::cin.get();
    return 0;
}
