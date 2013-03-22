#include "Preference.hpp"

Preference::Preference ( void )
{
        this->setBackgroundColor ( Color3f ( 1,1,1 ) );
        this->setWireColor ( Color3f ( 0,0,0 ) );
        this->setSurfaceColor ( Color3f ( 0.7f, 0, 0 ) );
        this->setRenderingMode ( SURFACE );
        return;
}
Preference:: ~Preference ( void )
{
        return;
}

void
Preference::setBackgroundColor ( const Color3f c )
{
        this->_background = c;
        return;
}

void
Preference::setWireColor ( const Color3f c )
{
        this->_wire = c;
        return;
}

void
Preference::setSurfaceColor ( const Color3f c )
{
        this->_surface = c;
        return;
}

void
Preference::setRenderingMode ( const RenderingMode status )
{
        this->_status = status;
}
Color3f
Preference::getBackgroundColor ( void ) const
{
        return _background;
}
Color3f
Preference::getWireColor ( void ) const
{
        return _wire;
}
Color3f
Preference::getSurfaceColor ( void ) const
{
        return _surface;
}

RenderingMode
Preference::getRenderingMode ( void ) const
{
        return this->_status;
}
