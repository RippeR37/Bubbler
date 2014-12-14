#ifndef VIEW_FLOOR_H_INCLUDED
#define VIEW_FLOOR_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/Floor.h"


namespace View {

    class ViewFloor : public ExtendedView<Model::Floor> {
        public:
            ViewFloor();
            ~ViewFloor();
            
            void render(const Model::Floor& floor);

        private:
            void setVertexData(const Model::Floor& floor);
    };

}

#endif