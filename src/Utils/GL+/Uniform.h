#ifndef UTILS_GL_UNIFORM_H_INCLUDED
#define UTILS_GL_UNIFORM_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace GL {

    class Uniform {
        public:
            Uniform();
            Uniform(GLuint location);
            ~Uniform();

            GLuint getLocation() const;
            
            void setSampler(GLint value);

        public:
            template<typename T> void set(T v0);
            template<typename T> void set(T v0, T v1);
            template<typename T> void set(T v0, T v1, T v2);
            template<typename T> void set(T v0, T v1, T v2, T v3);
            
            template<typename T> void setVec(const T& value, GLsizei count = 1);
            template<typename T> void setMatrix(const T& value, GLsizei count = 1, GLboolean transpose = GL_FALSE);

        private:
            GLuint _location;
    };

}

#endif