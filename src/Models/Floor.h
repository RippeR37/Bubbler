#ifndef MODEL_FLOOR_H_INCLUDED
#define MODEL_FLOOR_H_INCLUDED

namespace Model {

    class Floor {
        public:
            Floor();
            ~Floor();

            float getInterval() const;
            float getStartX() const;
            float getStartY() const;
            float getEndX() const;
            float getEndY() const;

        private:
            float _interval;
            float _startX;
            float _startY;
            float _endX;
            float _endY;
    };

}

#endif