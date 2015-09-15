#ifndef ARENDERER_HPP
#define ARENDERER_HPP

#include "src/parser/COption.hpp"

class QHBoxLayout;

class ARenderer {
    public:
        ARenderer(COption *option);
        virtual QHBoxLayout *render() = 0;
    protected:
        COption *_option;
};

#endif // ARENDERER_HPP
