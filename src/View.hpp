#ifndef __VIEW_HPP__
#define __VIEW_HPP__ 1
#include "Model.hpp"
class View
{
private:
        Model& _model;
public:
        View ( Model& model );
        virtual ~View ( void );
        void init ( void );
        void render ( void );
        void resize ( const int width, const int height );
private:
        void render_mesh ( void );
        void setLight ( const Light& light );
};
#endif // __VIEW_HPP__
