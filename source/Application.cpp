#include <iostream>
#include <stdexcept>

extern "C" {
    #include "glad/glad.h"
    #include "glfw3.h"
}

#include "Application.hpp"


#define PROGNAME        "PolyCepharithm"
#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600

Window::Window(std::int32_t w, std::int32_t h) 
: m_width(w), m_height(h), handle(nullptr) {
    glfwSetErrorCallback(errorCallback);
    
    if (glfwInit() == GLFW_FALSE) 
        throw std::runtime_error("Unable to initialize GLFW");
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    handle = glfwCreateWindow(w, h, PROGNAME, nullptr, nullptr);
    if (handle == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Unable to create GLFW window");
    }
    
    glfwGetFramebufferSize(handle, &m_width, &m_height);
    glfwSetWindowUserPointer(handle, this);

    glfwMakeContextCurrent(handle);
    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(handle);
        glfwTerminate();
        throw std::runtime_error("Unable to load GL loader");
    }

    glfwSetFramebufferSizeCallback(handle, frameBufferSizeCallback);
}

Window::~Window(void) {
    if (handle != nullptr)
        glfwDestroyWindow(handle);
    glfwTerminate();
}

void Window::errorCallback(int code, char const *description) { 
    std::cerr << "GLFW error 0x" << std::hex << code << ": " << description << '\n'; 
}

void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self == nullptr)
        return;

    self->m_width  = width;
    self->m_height = height;
    glViewport(0, 0, width, height);
}

Application::Application() : 
    m_state(State::UNINITIALIZED), 
    m_window(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

void Application::run() {
    while(!glfwWindowShouldClose(m_window.handle)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_window.handle);
        glfwPollEvents();
    }
}