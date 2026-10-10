#ifndef GL_PROGRAM_HPP
#define GL_PROGRAM_HPP

#include <cstdint>

namespace GL {
    // Forward declarations
    class Shader;
    typedef unsigned int GLuint;

    
    class Program {
    private:
        GLuint m_progid;
    public:
        // Constructor reads and builds the shader
        Program(Shader const &vertex, Shader const &fragment);
        explicit Program(Shader const &compute);
        ~Program();

        Program(Program const &)            = delete;
        Program& operator=(Program const &) = delete;

        void use(void) const;
        GLuint id(void) const { return m_progid; }
    };
}


#endif