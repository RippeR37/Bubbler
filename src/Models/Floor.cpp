#include "Floor.h"

namespace Model {

    Floor::Floor() {
        _interval =  1.0f;
        _startX   =  0.0f;
        _startY   =  0.0f;
        _endX     =  5.0f;
        _endY     = 10.0f;
    }

    Floor::~Floor() {

    }

    float Floor::getInterval() const {
        return _interval;
    }

    float Floor::getStartX() const {
        return _startX;
    }

    float Floor::getStartY() const {
        return _startY;
    }

    float Floor::getEndX() const {
        return _endX;
    }

    float Floor::getEndY() const {
        return _endY;
    }

}