#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <cstdint>


typedef struct GLFWwindow GLFWwindow;

enum class State {
    UNINITIALIZED = 0,
    INITIALIZED,
    RUNNING,
    PAUSED
};

class Window {
    private:
        std::int32_t m_width, m_height;
        
    public:
        GLFWwindow  *handle = nullptr;
        
        Window(std::int32_t, std::int32_t);
        Window(Window const &)            = delete;
        Window& operator=(Window const &) = delete;
        Window(Window&&)                  = delete;
        Window& operator=(Window &&)      = delete;
        ~Window();

        void setWidth(std::int32_t  w)      { m_width = w;     }
        std::uint32_t getWidth(void) const  { return m_width;  }
        void setHeight(std::int32_t h)      { m_height = h;    }
        std::uint32_t getHeight(void) const { return m_height; }
    
    private:
        static void errorCallback(int, char const *);
        static void frameBufferSizeCallback(GLFWwindow*, int, int);
};

class Application {
    private:
        State  m_state;
        Window m_window;
        
    public:
        Application();
        void run(void);

        State getState(void) const  { return m_state;  }
        void  setState(State state) { m_state = state; }
};

#endif