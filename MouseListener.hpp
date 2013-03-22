#ifndef __MOUSE_LISTERNER_HPP__
#define __MOUSE_LISTERNER_HPP__ 1
#include "MouseEvent.hpp"

class MouseListener
{
private:

public:
        MouseListener ( void );
        virtual ~MouseListener ( void );
        virtual bool mousePressed ( const MouseEvent* event );
        virtual bool mouseMoved ( const MouseEvent* event );
        virtual bool mouseReleased ( const MouseEvent* event );
};
#endif// __MOUSE_LISTERNER_HPP__


