#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include <cstdint>
#include <string>
#include <filesystem>

namespace GL {
    class Shader {
    private:
        std::uint32_t m_shaderid;
    public:
        Shader(std::filesystem::path filename);
        ~Shader();

        Shader(Shader const &)             = delete;
        Shader &operator =(Shader const &) = delete;

        std::uint32_t shaderID(void) const noexcept { return m_shaderid; }
    };
}

#endif