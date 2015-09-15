#ifndef CCHECKBOXRENDERER_HPP
#define CCHECKBOXRENDERER_HPP

#include "ARenderer.hpp"

class CCheckboxRenderer : public ARenderer {
    public:
        CCheckboxRenderer(COptionCheckbox *option);
        QHBoxLayout *render();
};

#endif // CCHECKBOXRENDERER_HPP
