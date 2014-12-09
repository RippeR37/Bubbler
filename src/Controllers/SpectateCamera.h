#ifndef CONTROLLER_SPECTATECAMERA_H_INCLUDED
#define CONTROLLER_SPECTATECAMERA_H_INCLUDED

#include "Camera.h"
#include "../Models/Aquarium.h"

#include <glm/glm.hpp>

namespace Controller {

    class SpectateCamera : public Camera {
        public:
            SpectateCamera();
            ~SpectateCamera();

            void init(const Model::Aquarium& aquarium);

            void update(double deltaTime);
            void updateMouse(double x, double y);
            void updateKeyboard(int key, int scancode, int action, int mods);
            void updateMouseWheel(double x, double y);

            const glm::vec2  getPos2D() const;
            const glm::vec3& getPos3D() const;
            const glm::mat4& getMatrix() const;
            
        private:
    };

}

#endif