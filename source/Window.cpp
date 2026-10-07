#include <iostream>
#include <stdexcept>

extern "C" {
    #include "glad/glad.h"
    #include "glfw3.h"
}

#include "Window.hpp"

Window::Window(std::string const title, std::int32_t width, std::int32_t height) : 
    m_width(width), 
    m_height(height) 
{
    glfwSetErrorCallback(errorCallback);

    // Init Window
    if (glfwInit() == GLFW_FALSE) 
        throw std::runtime_error("Unable to initialize GLFW");
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (m_handle == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Unable to create GLFW window");
    }
    
    glfwMakeContextCurrent(m_handle);
    
    // Init GLAD (OpenGL)
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
        throw std::runtime_error("Unable to load GL loader");
    }
    
    // Window Setup
    glfwSetWindowUserPointer(m_handle, this);
    glfwGetFramebufferSize(m_handle, &m_framebuf_width, &m_framebuf_height);
    
    // Window Callbacks
    glfwSetFramebufferSizeCallback(m_handle, frameBufferSizeCallback);
    glfwSetWindowSizeCallback(m_handle, windowSizeCallback);
}

Window::~Window(void) {
    if (m_handle != nullptr)
        glfwDestroyWindow(m_handle);
    glfwTerminate();
}

void Window::errorCallback(int code, char const *description) { 
    std::cerr << "GLFW error 0x" << std::hex << code << ": " << description << '\n'; 
}

void Window::frameBufferSizeCallback(GLFWwindow* window, int fb_width, int fb_height) {
    Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self == nullptr) {
        std::cerr << "ERROR: Unable to resize window frame buffer.\n";
        return;
    }

    self->m_framebuf_width  = fb_width;
    self->m_framebuf_height = fb_height;
    glViewport(0, 0, fb_width, fb_height);
}

void Window::windowSizeCallback(GLFWwindow *window, int width, int height) {
    Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self == nullptr) {
        std::cerr << "ERROR: Unable to resize window frame.\n";
        return;
    } 

    self->m_width  = width;
    self->m_height = height;
}