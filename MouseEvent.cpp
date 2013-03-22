#include "MouseEvent.hpp"
#include <sstream>
MouseEvent::MouseEvent ( const int width, const int height, const int x, const int y, const unsigned char button ) : _width ( width ), _height ( height ), _x ( x ), _y ( y ), _button ( button )
{
        return;
}
MouseEvent::MouseEvent ( const MouseEvent& that )
{
        this->copy ( that );
        return;
}
MouseEvent&
MouseEvent::operator = ( const MouseEvent& that )
{
        this->copy ( that );
        return *this;
}
MouseEvent::~MouseEvent ( void )
{
        return;
}

int
MouseEvent::x ( void ) const
{
        return this->_x;
}
int
MouseEvent::y ( void ) const
{
        return this->_y;
}

int
MouseEvent::width ( void ) const
{
        return this->_width;
}

int
MouseEvent::height ( void ) const
{
        return this->_height;
}

unsigned char
MouseEvent::buttons ( void ) const
{
        return this->_button;
}

bool
MouseEvent::isLeftButtonPressed ( void ) const
{
        return this->buttons() & MOUSE_LEFT_BUTTON;
}
bool
MouseEvent::isMiddleButtonPressed ( void ) const
{
        return this->buttons() & MOUSE_MIDDLE_BUTTON;
}
bool
MouseEvent::isRightButtonPressed ( void ) const
{
        return this->buttons() & MOUSE_RIGHT_BUTTON;
}

std::string
MouseEvent::toString ( void ) const
{
        std::stringstream ss;
        ss<<"("<<this->width() <<", "<<this->height() <<")";
        ss<<"("<<this->x() <<", "<<this->y() <<")";
        if ( this->isLeftButtonPressed() ) ss<<"y";
        else ss<<"n";
        if ( this->isMiddleButtonPressed() ) ss<<"y";
        else ss<<"n";
        if ( this->isRightButtonPressed() ) ss<<"y";
        else ss<<"n";
        return ss.str();
}

void
MouseEvent::copy ( const MouseEvent &that )
{
        this->_x = that._x;
        this->_y = that._y;
        this->_width = that._width;
        this->_height = that._height;
        this->_button = that._button;
        return;
}
