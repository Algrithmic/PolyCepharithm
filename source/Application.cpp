#include <iostream>
#include <stdexcept>

extern "C" {
    #include "glad/glad.h"
    #include "glfw3.h"
}

#include "Application.hpp"


Application::Application() : 
    m_state(State::UNINITIALIZED), 
    m_window("Physarithm") {

}

void Application::run() {
    while(!glfwWindowShouldClose(m_window.handle())) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_window.handle());
        glfwPollEvents();
    }
}