#ifndef CONTROLLER_STATE_GAMEPLAY_H_INCLUDED
#define CONTROLLER_STATE_GAMEPLAY_H_INCLUDED

#include "../State.h"
#include "../LockedCamera.h"
#include "../SpectateCamera.h"

#include "../../Models/Floor.h"
#include "../../Models/Aquarium.h"
#include "../../Models/Player.h"
#include "../../Models/Bubbles.h"
#include "../../Models/CameraType.h"

#include "../../Views/ViewFloor.h"
#include "../../Views/ViewAquarium.h"
#include "../../Views/ViewBubble.h"

#include "../../Utils/GL+/Pipeline.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Controller {

    class State::Gameplay : public State {
        public:
            Gameplay();

            void update(const double frameTime);
            void render();

            void onLoad();
            void onUnload();
            
            Camera& getCamera();
            LockedCamera& getLockedCamera();
            SpectateCamera& getSpectateCamera();
            Model::Aquarium& getAquarium();
            Model::Player& getPlayer();
            GL::Pipeline& getPipeline();
            Model::CameraType getCameraType() const;

            static void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void handleMouseMovement(GLFWwindow* window, double x, double y);
            static void handleMouseScrolling(GLFWwindow* window, double x, double y);

        private:
            void setCamera(Model::CameraType cameraType);
            bool isEnd() const;

            Camera& _camera;
            LockedCamera _lockedCamera;
            SpectateCamera _spectateCamera;
            Model::CameraType _cameraType;
            GL::Pipeline _pipeline;

        private:
            Model::Floor _floor;
            Model::Aquarium _aquarium;
            Model::Player _player;
            Model::Bubbles _bubbles;

        private:
            View::ViewFloor _viewFloor;
            View::ViewAquarium _viewAquarium;
            View::ViewBubble _viewBubble;
    };

}

#endif