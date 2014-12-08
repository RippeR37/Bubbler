#ifndef VIEW_ABSTRACT_H_INCLUDED
#define VIEW_ABSTRACT_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace View {

    template<typename T>
    class View {
        public:
            virtual void init(const T& object) = 0;
            virtual void render(const T& object) = 0;

    };

    template<>
    class View<void> {
        public:
            virtual void init() = 0;
            virtual void render() = 0;

    };

}

#endif