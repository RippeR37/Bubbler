#ifndef VIEW_BUBBLE_H_INCLUDED
#define VIEW_BUBBLE_H_INCLUDED

#include "ExtendedView.h"
#include "../Models/Bubble.h"

namespace View {

    class ViewBubble : public ExtendedView<Model::Bubble> {
        public:
            ViewBubble();
            ~ViewBubble();
            
            void render(const Model::Bubble& bubble);
            
            static int assignLigtbubblePositions(glm::vec3* lightbubblePosition, unsigned int lights);

        private:
            void setVertexData(const Model::Bubble& bubble);
    };

}

#endif