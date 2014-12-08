#ifndef UTILS_GL_SHADER_H_INCLUDED
#define UTILS_GL_SHADER_H_INCLUDED

#include "../Exception.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>

namespace GL {

    class Shader {
        public:
            enum class Type : GLenum {
                VertexShader   = GL_VERTEX_SHADER,
                FragmentShader = GL_FRAGMENT_SHADER,
                GeometryShader = GL_GEOMETRY_SHADER,
            };

        public:
            Shader(Type type);
            Shader(const std::string& path, Type type);
            Shader(Shader&& shader);
            ~Shader();

            Shader& operator=(Shader&& shader);

            GLuint getID() const;
            Type getType() const;

        private:
            Shader& operator=(const Shader&);
            Shader(const Shader&);

            void create(Type type);
            void destroy();
            void load(const std::string& path, Type type);
            bool compile() throw(Util::Exception::FatalError);
            
            bool _compiled;
            Type _type;
            GLuint _shaderID;
            std::string _path;
            std::string _code;

        public:
            friend class Program;
    };

}

#endif