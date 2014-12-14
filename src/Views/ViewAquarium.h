#ifndef VIEW_AQUARIUM_H_INCLUDED
#define VIEW_AQUARIUM_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/Aquarium.h"

namespace View {

    class ViewAquarium : public ExtendedView<Model::Aquarium> {
        public:
            ViewAquarium();
            ~ViewAquarium();
            
            void render(const Model::Aquarium& aquarium);

        private:
            void setVertexData(const Model::Aquarium& aquarium);
    };

}

#endif