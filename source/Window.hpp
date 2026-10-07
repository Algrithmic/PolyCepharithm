#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstdint>
#include <string>

typedef struct GLFWwindow GLFWwindow;

class Window {
    private:
        static constexpr std::int32_t DEFAULT_WIDTH  = 800;
        static constexpr std::int32_t DEFAULT_HEIGHT = 600;

        std::int32_t m_width  = DEFAULT_WIDTH;
        std::int32_t m_height = DEFAULT_HEIGHT;
        std::int32_t m_framebuf_width  = 0;
        std::int32_t m_framebuf_height = 0;
        GLFWwindow  *m_handle = nullptr;
        
    public:
        Window(std::string const title, 
               std::int32_t w = DEFAULT_WIDTH, 
               std::int32_t h = DEFAULT_HEIGHT);
        ~Window();

        Window(Window const &)              = delete;
        Window &operator = (Window const &) = delete;
        Window(Window&&)                    = delete;
        Window &operator = (Window &&)      = delete;

        std::int32_t width(void)  const noexcept { return m_width;  }
        std::int32_t height(void) const noexcept { return m_height; }
        std::int32_t frameBufferWidth(void)  const noexcept { return m_framebuf_width;  }
        std::int32_t frameBufferHeight(void) const noexcept { return m_framebuf_height; }
        GLFWwindow  *handle(void) const noexcept { return m_handle; } 

    private:
        static void errorCallback(int, char const *);
        static void frameBufferSizeCallback(GLFWwindow *, int, int);
        static void windowSizeCallback(GLFWwindow *, int, int);
};      

#endif