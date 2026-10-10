#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <cstdint>

namespace GL {
    // forward declarations 
    // (C-Style Data Types used to stay consistent with GLAD API)
    typedef unsigned int GLenum;
    typedef unsigned int GLuint;
    typedef          int GLint;
    typedef          int GLsizei;

    class VertexBuffer {
    private:
        GLuint m_vbo = 0;
    public:
        VertexBuffer();
        ~VertexBuffer();

        inline void bind(void);
        void upload(void const *data, 
                    std::size_t bytes, 
                    GLenum usage);
        void update(void const *data, 
                    std::size_t bytes, 
                    std::size_t offset = 0);
        GLuint id(void) { return m_vbo; }
    };

    class VertexArray {
    private:
        GLuint m_vao = 0;
    public:
        VertexArray();
        ~VertexArray();

        void bind(void);
        void setAttribute(VertexBuffer& vbo, 
                          GLuint location, 
                          GLint components, 
                          GLsizei stride, 
                          std::size_t offset, 
                          GLuint divisor = 0);
        GLuint id(void) { return m_vao; }
    };
}
    
#endif