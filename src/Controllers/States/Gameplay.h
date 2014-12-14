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
#include "../../Views/ViewBubble.h"
#include "../../Views/ViewAquarium.h"

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

            void handleUpdate();
            
            unsigned int getLevel() const;
            Camera& getCamera();
            LockedCamera& getLockedCamera();
            SpectateCamera& getSpectateCamera();

            Model::Player& getPlayer();
            Model::Bubbles& getBubbles();
            Model::Aquarium& getAquarium();
            Model::CameraType getCameraType() const;

            GL::Pipeline& getPipeline();

            static void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void handleMouseMovement(GLFWwindow* window, double x, double y);
            static void handleMouseScrolling(GLFWwindow* window, double x, double y);

        private:
            void setCamera(Model::CameraType cameraType);
            void setNextLevel();
            bool isEnd() const;

            unsigned int _level;
            Camera& _camera;
            LockedCamera _lockedCamera;
            SpectateCamera _spectateCamera;

        private:
            GL::Pipeline _pipeline;

        private:
            Model::Floor _floor;
            Model::Player _player;
            Model::Bubbles _bubbles;
            Model::Aquarium _aquarium;
            Model::CameraType _cameraType;

        private:
            View::ViewFloor _viewFloor;
            View::ViewBubble _viewBubble;
            View::ViewAquarium _viewAquarium;
    };

}

#endif