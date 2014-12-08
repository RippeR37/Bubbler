#ifndef CONTROLLER_CAMERA_H_INCLUDED
#define CONTROLLER_CAMERA_H_INCLUDED

#include <glm/glm.hpp>

namespace Controller {

    class Camera {
        public:
            Camera();
            virtual ~Camera();

            virtual void update(double deltaTime) = 0;
            virtual void updateMouse(double x, double y) = 0;
            virtual void updateKeyboard(int key, int scancode, int action, int mods) = 0;

            virtual const glm::vec2  getPos2D() = 0;
            virtual const glm::vec3& getPos3D() = 0;
            virtual const glm::mat4& getMatrix() = 0;

        protected:
            glm::mat4 _matrix;
    };

}

#endif