#ifndef GL_PROGRAM_HPP
#define GL_PROGRAM_HPP

#include <cstdint>

namespace GL {
    class Shader;   // Forward declaration
    

    class Program {
    private:
        std::uint32_t m_progid;
    public:
        // Constructor reads and builds the shader
        Program(Shader const &vertex, Shader const &fragment);
        explicit Program(Shader const &compute);
        ~Program();

        Program(Program const &)            = delete;
        Program& operator=(Program const &) = delete;

        void use(void) const;
        std::uint32_t id(void) const { return m_progid; }
    };
}


#endif