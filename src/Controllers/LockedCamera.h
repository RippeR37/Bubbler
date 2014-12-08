#ifndef CONTROLLER_LOCKEDCAMERA_H_INCLUDED
#define CONTROLLER_LOCKEDCAMERA_H_INCLUDED

#include "Camera.h"

#include <glm/glm.hpp>

namespace Controller {

    class LockedCamera : public Camera {
        public:
            LockedCamera();
            ~LockedCamera();

            void update(double deltaTime);
            void updateMouse(double x, double y);
            void updateKeyboard(int key, int scancode, int action, int mods);

            const glm::vec2  getPos2D();
            const glm::vec3& getPos3D();
            const glm::mat4& getMatrix();

        private:
            float _speed;
            float _angleX;
            float _angleY;
            float _mouseSpeed;
    };

}

#endif