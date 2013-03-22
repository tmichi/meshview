#include "GLWidget.hpp"
#include "MouseEvent.hpp"
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

GLWidget::GLWidget ( Model& model,  View& view, QWidget *parent )
        : QGLWidget ( QGLFormat ( QGL::SampleBuffers ), parent ), _model ( model ), _view ( view )
{
        this->_ball = new VirtualTrackball ( model );
        return;
}

GLWidget::~GLWidget ( void )
{
        delete this->_ball;
        return;
}

QSize
GLWidget::minimumSizeHint ( void ) const
{
        return QSize ( 50, 50 );
}
QSize
GLWidget::sizeHint ( void ) const
{
        return QSize ( 2400, 1600 );
}


void
GLWidget::initializeGL ( void  )
{
        this->_view.init();
        return;
}

void
GLWidget::paintGL ( void )
{
        this->_view.render();
        return;
}
void
GLWidget::resizeGL ( int width, int height )
{
        this->_view.resize ( width, height );

        return;
}

void
GLWidget::mousePressEvent ( QMouseEvent* event )
{
        MouseEvent e = this->convert_qmouse_event ( event );
        this->_ball->mousePressed ( &e );
        return;
};

void
GLWidget::mouseMoveEvent ( QMouseEvent* event )
{
        MouseEvent e = this->convert_qmouse_event ( event );
        if ( this->_ball->mouseMoved ( &e ) ) {
                updateGL();
                emit mouseDragged ( event->x(), event->y() );
        }
};

void
GLWidget::mouseReleaseEvent ( QMouseEvent* event )
{
        MouseEvent e = this->convert_qmouse_event ( event );
        this->_ball->mouseReleased ( &e );
        return;
}

MouseEvent
GLWidget::convert_qmouse_event ( QMouseEvent* event )
{
        unsigned char button = 0x00;
        if ( event->buttons() & Qt::LeftButton ) button   += 0x01;
        if ( event->buttons() & Qt::MiddleButton ) button += 0x02;
        if ( event->buttons() & Qt::RightButton ) button  += 0x04;
        const int x = event->pos().x();
        const int y = event->pos().y();
        return MouseEvent ( this->width(), this->height(), x, y, button );
}
