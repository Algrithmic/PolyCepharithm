#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <string>

extern "C" {
    #include "glad/glad.h"
}

#include "GL/Program.hpp"
#include "GL/Shader.hpp"

namespace {
    std::int32_t programCompilationStatus(std::uint32_t program) {
        using namespace std;
        
        constexpr size_t msg_size = 512;
        int32_t success = 0;
        string info_log(msg_size, '\0');

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, msg_size, nullptr, info_log.data());
            cerr << "ERROR : SHADER PROGRAM - Linking Failure\n";
            cerr << info_log.c_str() << '\n';
        }
        return success;
    }
}

namespace GL {
    Program::Program(Shader const &vertex, Shader const &fragment) {
        m_progid = glCreateProgram();
    
        // Successful compilation
        glAttachShader(m_progid, vertex.shaderID());
        glAttachShader(m_progid, fragment.shaderID());

        // link
        glLinkProgram(m_progid);

        if (!programCompilationStatus(m_progid)) {
            glDeleteProgram(m_progid);
            throw std::runtime_error("Shader Program Compilation Failure");
        }
    }

    Program::Program(Shader const &compute) {
        m_progid = glCreateProgram();
    
        // Successful compilation
        glAttachShader(m_progid, compute.shaderID());

        // link
        glLinkProgram(m_progid);

        if (!programCompilationStatus(m_progid)) {
            glDeleteProgram(m_progid);
            throw std::runtime_error("Shader Program Compilation Failure");
        }
    }

    Program::~Program() {
        glDeleteProgram(m_progid);
    }

    void Program::use(void) const {
        glUseProgram(m_progid);
    }
}