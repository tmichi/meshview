#ifndef __CHANGE_COLOR_WIDGET_HPP__
#define __CHANGE_COLOR_WIDGET_HPP__ 1
#include <QLabel>
#include <QWidget>
class ChangeColorWidget : public QWidget
{
Q_OBJECT //お約束
private:
	QLabel* _faceColorLabel;
public:
	ChangeColorWidget( QColor faceColor,  QWidget *parent = 0);
	QColor getSurfaceColor( void ) const ;
public slots : 
	void set_surface_color( void ) ;
signals :
	void updated();
};
#endif //__CHANGE_COLOR_WIDGET_HPP__