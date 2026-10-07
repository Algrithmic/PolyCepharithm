#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <cstdint>

#include "Window.hpp"

enum class State {
    UNINITIALIZED = 0,
    INITIALIZED,
    RUNNING,
    PAUSED
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