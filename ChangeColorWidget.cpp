#include "ChangeColorWidget.hpp"
#include <QtWidgets>

ChangeColorWidget::ChangeColorWidget(const QColor faceColor,  QWidget *parent ) : QWidget(parent) {
	QHBoxLayout *hBoxLayout1 = new QHBoxLayout;
	QPushButton *button3 = new QPushButton ( tr ( "Face Color" ) ) ;
	
	this->_faceColorLabel = new QLabel;
	this->_faceColorLabel->setFrameStyle ( QFrame::Sunken | QFrame::Panel );
	this->_faceColorLabel->setPalette ( faceColor );
	this->_faceColorLabel->setAutoFillBackground ( true );

	connect (button3, SIGNAL(pressed()), this, SLOT(set_surface_color()));

	hBoxLayout1->addWidget ( button3 );
	hBoxLayout1->addWidget ( this->_faceColorLabel );
	
	this->setLayout(hBoxLayout1);
	return;
}

void 
ChangeColorWidget::set_surface_color( void ) {
	QColor color = QColorDialog::getColor ( this->getSurfaceColor(), this );
	if ( color.isValid() ) {
		this->_faceColorLabel->setPalette ( QPalette ( color ) );
		this->_faceColorLabel->setAutoFillBackground ( true );
		emit updated();
	}
	return;
}

QColor
ChangeColorWidget::getSurfaceColor( void ) const {
	return this->_faceColorLabel->palette().color(QPalette::Window);
}
