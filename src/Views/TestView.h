#ifndef VIEW_TEST_H_INCLUDED
#define VIEW_TEST_H_INCLUDED

#include "ExtendedView.h"

namespace View {

    class TestView : public ExtendedView<void> {
        public:
            TestView();
            ~TestView();
            
            void render();

        private:
            void setVertexData();
    };

}

#endif