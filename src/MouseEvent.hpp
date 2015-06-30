#ifndef __MOUSE_EVENT_HPP__
#define __MOUSE_EVENT_HPP__ 1
#include <cstdlib>
#include <string>
#define MOUSE_LEFT_BUTTON 0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON 0x04

class MouseEvent
{
private:
        int _width;
        int _height;
        int _x;
        int _y;
        unsigned char _button;
public:
        MouseEvent ( const int width, const int height, const int x, const int y, unsigned char button );
        MouseEvent ( const MouseEvent& that );
        MouseEvent& operator = ( const MouseEvent& that );
        virtual ~MouseEvent ( void );

        int x ( void ) const ;
        int y ( void ) const ;
        int width ( void ) const ;
        int height ( void ) const ;
        bool isLeftButtonPressed ( void ) const;
        bool isMiddleButtonPressed ( void ) const;
        bool isRightButtonPressed ( void ) const;
        unsigned char buttons ( void ) const;
        std::string toString ( void ) const ;
private:
        void copy ( const MouseEvent &that );
};

#endif //__MOUSE_EVENT_HPP__
