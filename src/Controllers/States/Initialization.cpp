#include "Initialization.h"
#include "../../Models/States.h"
#include "../../Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ctime>
#include <cstdlib>

namespace Controller {

    void State::Initialization::update(double frameTime) {
        // do nothing
    }

    void State::Initialization::render() {
        // do nothing
    }

    void State::Initialization::onLoad() {
        setRandomSeed();
        openWindow();
        initializeStates();

        State::changeTo(Model::States::get().gameplay);
    }

    void State::Initialization::onUnload() {

    }

    void State::Initialization::openWindow() {
        Game::get()._window = new Util::Window();
        Game::get().getWindow().setSize(800, 600);
        Game::get().getWindow().setTitle("Bubbler");
        
        if(Game::get().getWindow().create() == false)
            throw Util::Exception::FatalError(std::string("Failed to create window."));
    }

    void State::Initialization::setRandomSeed() {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    void State::Initialization::initializeStates() {
        Model::States::get().initialize();
    }

}
