#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdexcept>

extern "C" {
    #include "glad/glad.h"
}

#include "GL/Shader.hpp"

namespace {
    GLint shaderCompilationStatus(GLuint shader, std::string const &filename) {
        using namespace std;
        
        constexpr size_t msg_size = 512;
        GLint success = 0;
        string info_log(msg_size, '\0');

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, msg_size, nullptr, info_log.data());
            cerr << "ERROR: SHADER " << filename << " - Compilation Failure\n";
            cerr << info_log.c_str() << '\n';
        }

        return success;
    }

    const std::unordered_map<std::string, GLenum> shader_type = {
        { ".vert", GL_VERTEX_SHADER   },
        { ".frag", GL_FRAGMENT_SHADER },
        { ".comp", GL_COMPUTE_SHADER  }
    };
}

namespace GL {
    Shader::Shader(std::filesystem::path filepath) {
        using namespace std;

        ifstream ihandle(filepath, std::ios::binary);
        if (!ihandle.is_open()) {
            cout << "Cannot open file: " << filepath.filename() << "\n";
            throw std::runtime_error("Unable to open file");
        }

        // Read and store the entire content of the file
        string contents(filesystem::file_size(filepath), '\0');
        ihandle.read(contents.data(), contents.size());

        ihandle.close();

        m_shaderid = glCreateShader(shader_type.at(filepath.extension().string()));
        char const *source = contents.c_str();
        glShaderSource(m_shaderid, 1, &source, nullptr);
        glCompileShader(m_shaderid);

        if (!shaderCompilationStatus(m_shaderid, filepath.filename().string())) {
            glDeleteShader(m_shaderid);
            throw std::runtime_error("Shader Compilation Failure");
        }
    }

    Shader::~Shader() {
        glDeleteShader(m_shaderid);
    }
}