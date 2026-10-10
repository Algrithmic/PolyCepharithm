#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include <cstdint>
#include <string>
#include <filesystem>

namespace GL {
    typedef unsigned int GLuint;

    class Shader {
    private:
        GLuint m_shaderid;
    public:
        explicit Shader(std::filesystem::path filename);
        ~Shader();

        Shader(Shader const &)             = delete;
        Shader &operator =(Shader const &) = delete;

        GLuint shaderID(void) const noexcept { return m_shaderid; }
    };
}

#endif