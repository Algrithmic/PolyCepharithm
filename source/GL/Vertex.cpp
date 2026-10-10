#include <iostream>

extern "C" {
    #include "glad/glad.h"
}

#include "GL/Vertex.hpp"

namespace GL {
    // VertexBuffer Class definitions
    inline VertexBuffer::VertexBuffer()  { glGenBuffers(1, &m_vbo);    }
    inline VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &m_vbo); }
    inline void VertexBuffer::bind(void) { glBindBuffer(GL_ARRAY_BUFFER, m_vbo); }
    inline void VertexBuffer::upload(void const *data, std::size_t bytes, GLenum usage) { 
        bind();
        glBufferData(GL_ARRAY_BUFFER, bytes, data, usage);
    }
    inline void VertexBuffer::update(void const *data, std::size_t bytes, std::size_t offset) {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, bytes, data);
    }

    // VertexArray Class definitions
    inline VertexArray::VertexArray()   { glGenVertexArrays(1, &m_vao);    }
    inline VertexArray::~VertexArray()  { glDeleteVertexArrays(1, &m_vao); }
    inline void VertexArray::bind(void) { glBindVertexArray(m_vao);        }
    void VertexArray::setAttribute(VertexBuffer &vbo, GLuint location, 
                                   GLint components, GLsizei stride, 
                                   std::size_t offset, GLuint divisor) {
        bind();
        vbo.bind();
        glVertexAttribPointer(location, components, GL_FLOAT, GL_FALSE, stride, 
                              reinterpret_cast<void *>(offset));
        glEnableVertexAttribArray(location);
        glVertexAttribDivisor(location, divisor);
    }
}