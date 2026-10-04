#include <iostream>

extern "C" {
    #include "glad/glad.h"
    #include "glfw3.h"
}

int main( void ) {
    if (!glfwInit()) 
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello", nullptr, nullptr);
    if (!window) { 
        glfwTerminate(); 
        return -1; 
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}