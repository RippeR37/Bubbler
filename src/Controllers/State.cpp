#include "State.h"
#include "../Game.h"
#include "../Models/States.h"

namespace Controller {

    State::State() {
        next = this;
    }

    State::~State() {
        next = nullptr;
    }

    void State::handleInput() {
        if(shouldSkip())
            return;

        if(glfwWindowShouldClose(Game::get().getWindow().getHandle()))
            changeTo(Model::States::get().shutdown);
    }

    State* State::getNext() {
        return next;
    }

    void State::changeTo(State* nextState) {
        next = nextState;
    }
    
    bool State::shouldSkip() {
        return (getNext() != this);
    }

    const State* const State::Quit = nullptr;

}