#include "MainWindow.hpp"
#include "GLWidget.hpp"
#include <QtWidgets>
MainWindow::MainWindow ( Model& model, View& view ) : _model ( model ), _view ( view )
{
        QWidget* widget = new QWidget;
        widget->setContentsMargins ( 5,5,5,5 );

        this->setCentralWidget ( widget );
        this->_glwidget = new GLWidget ( this->_model,  this->_view, widget );
        connect ( this->_glwidget, SIGNAL ( mouseDragged ( float, float ) ), this, SLOT ( mouse_dragged ( float, float ) ) );
        QRadioButton *radioButton1 = new QRadioButton ( tr ( "Wireframe" ) );
        QRadioButton *radioButton2 = new QRadioButton ( tr ( "Surface" ) );
        radioButton2->setChecked ( true );
        connect ( radioButton1, SIGNAL ( pressed() ), this, SLOT ( polygon_wireframe() ) );
        connect ( radioButton2, SIGNAL ( pressed() ), this, SLOT ( polygon_surface() ) );

        QVBoxLayout *boxLayout1 = new QVBoxLayout;
        boxLayout1->addWidget ( radioButton1 );
        boxLayout1->addWidget ( radioButton2 );
        boxLayout1->addStretch ( 1 );

        QGroupBox *groupBox1 = new QGroupBox ( tr ( "Rendering Mode" ) );
        groupBox1->setLayout ( boxLayout1 );

        QPushButton *button1 = new QPushButton ( tr ( "View Fit" ) ) ;
        QPushButton *button2 = new QPushButton ( tr ( "View Init" ) ) ;
        connect ( button1, SIGNAL ( pressed() ), this, SLOT ( view_fit() ) );
        connect ( button2, SIGNAL ( pressed() ), this, SLOT ( view_init() ) );
	


	int r,g,b;
	this->_model.getSurfaceColor ( r,g,b );
	QColor col(r,g,b);
	this->_colorWidget = new ChangeColorWidget(col);
	connect ( this->_colorWidget, SIGNAL(updated()), this, SLOT(update_surface_color()));
	
        QVBoxLayout *boxLayout3 = new QVBoxLayout;
        boxLayout3->addWidget ( groupBox1 );
        boxLayout3->addWidget ( button1 );
        boxLayout3->addWidget ( button2 );
	boxLayout3->addWidget ( this->_colorWidget);
        boxLayout3->addStretch ( 1 );
	
        QWidget* widget1 = new QWidget;
	widget1->setLayout(boxLayout3);
        QTabWidget* tabWidget1 = new QTabWidget;
        tabWidget1->addTab ( widget1, tr ( "Views" ) );
        tabWidget1->setMinimumWidth ( 250 );

        QHBoxLayout *layout = new QHBoxLayout;
        layout->setMargin ( 5 );
        layout->addWidget ( this->_glwidget );
        layout->addWidget ( tabWidget1 );
        widget->setLayout ( layout );

        QString message = tr ( "A context menu is available by right-clicking" );
        this->statusBar()->showMessage ( message );

        this->create_actions();
        this->create_menus();
        this->create_toolbars();
        this->setWindowTitle ( tr ( "Viewer" ) );
        this->setMinimumSize ( 800, 600 );
        this->resize ( 800, 600 );
        connect ( this, SIGNAL ( updated() ), this->_glwidget, SLOT ( updateGL() ) );
        return;
}

//Pop-up menu
void
MainWindow::contextMenuEvent ( QContextMenuEvent* event )
{
        QMenu menu ( this );
        menu.addAction ( this->_newAct );
        menu.addAction ( this->_openAct );
        menu.addAction ( this->_saveAct );
        menu.exec ( event->globalPos() );
        return;
}

void
MainWindow::create_actions ( void )
{
        //New
        this->_newAct = new QAction ( QIcon ( ":/resources/new.png" ),tr ( "&New" ), this );
        this->_newAct->setShortcuts ( QKeySequence::New );
        this->_newAct->setStatusTip ( "Create a new file" );
        connect ( this->_newAct, SIGNAL ( triggered() ), this, SLOT ( new_file() ) );
        connect ( this->_newAct, SIGNAL ( triggered() ), this->_glwidget, SLOT ( updateGL() ) );

        //Open
        this->_openAct = new QAction ( QIcon ( ":/resources/open.png" ),tr ( "&Open" ), this );
        this->_openAct->setShortcuts ( QKeySequence::Open );
        this->_openAct->setStatusTip ( "Open a file" );
        connect ( this->_openAct, SIGNAL ( triggered() ), this, SLOT ( open() ) );
        connect ( this->_openAct, SIGNAL ( triggered() ), this->_glwidget, SLOT ( updateGL() ) );

        //Save
        this->_saveAct = new QAction ( QIcon ( ":/resources/save.png" ),tr ( "&Save" ), this );
        this->_saveAct->setShortcuts ( QKeySequence::Save );
        this->_saveAct->setStatusTip ( "Save a file" );
        connect ( this->_saveAct, SIGNAL ( triggered() ), this, SLOT ( save() ) );

        //Open
        this->_openCameraAct = new QAction ( QIcon ( ":/resources/openCamera.png" ),tr ( "Open Camera" ), this );
        this->_openCameraAct->setStatusTip ( "Open a camera file" );
        connect ( this->_openCameraAct, SIGNAL ( triggered() ), this, SLOT ( openCamera() ) );
        connect ( this->_openCameraAct, SIGNAL ( triggered() ), this->_glwidget, SLOT ( updateGL() ) );

        //Save
        this->_saveCameraAct = new QAction ( QIcon ( ":/resources/saveCamera.png" ),tr ( "Save Camera" ), this );
        this->_saveCameraAct->setStatusTip ( "Save a camera file" );
        connect ( this->_saveCameraAct, SIGNAL ( triggered() ), this, SLOT ( saveCamera() ) );

        //Save
        this->_snapshotAct = new QAction ( QIcon ( ":/resources/save.png" ),tr ( "Snapshot" ), this );
        this->_snapshotAct->setStatusTip ( "Snapshot" );
        connect ( this->_snapshotAct, SIGNAL ( triggered() ), this, SLOT ( saveSnapshot() ) );

        //Exit
        this->_exitAct = new QAction ( tr ( "E&xit" ), this );
        this->_exitAct->setShortcuts ( QKeySequence::Quit );
        this->_exitAct->setStatusTip ( "Exit this application." );
        connect ( this->_exitAct, SIGNAL ( triggered() ), this, SLOT ( close() ) );

        return;
}
void
MainWindow::create_menus ( void )
{
        this->_fileMenu = menuBar()->addMenu ( tr ( "&File" ) );
        this->_fileMenu->addAction ( this->_newAct );
        this->_fileMenu->addAction ( this->_openAct );
        this->_fileMenu->addAction ( this->_saveAct );
        this->_fileMenu->addAction ( this->_openCameraAct );
        this->_fileMenu->addAction ( this->_saveCameraAct );
        this->_fileMenu->addAction ( this->_snapshotAct );
        this->_fileMenu->addSeparator();
        this->_fileMenu->addAction ( this->_exitAct );
        return;
}

void
MainWindow::create_toolbars ( void )
{
        this->_fileToolBar = addToolBar ( tr ( "File" ) );
        this->_fileToolBar->addAction ( this->_newAct );
        this->_fileToolBar->addAction ( this->_openAct );
        this->_fileToolBar->addAction ( this->_saveAct );
        this->_fileToolBar->addAction ( this->_openCameraAct );
        this->_fileToolBar->addAction ( this->_saveCameraAct );
        return ;
}

void
MainWindow::new_file ( void )
{
        this->_model.initMesh();
        QString message = tr ( "Initialized." );
        statusBar()->showMessage ( message );
        emit updated();
        return;
}

void
MainWindow::open ( void )
{
        QString filename = QFileDialog::getOpenFileName ( this, tr ( "Open file from" ), ".", tr ( "STL File (*.stl)" ) );
        if ( !this->_model.openMesh ( filename.toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
        } else emit updated();
        return;
}

void
MainWindow::save ( void )
{
        QString filename = QFileDialog::getSaveFileName ( this, tr ( "Save file to" ), ".", tr ( "STL File (*.stl)" ) );
        if ( !this->_model.saveMesh ( filename.toStdString() ) ) {
                QString  message ( tr ( "Save failed." ) );
                statusBar()->showMessage ( message );
        }
        return;
}

void
MainWindow::openCamera ( void )
{
        QString filename = QFileDialog::getOpenFileName ( this, tr ( "Open camera file from" ), ".", tr ( "CAM File (*.cam)" ) );
        if ( !this->_model.openCamera ( filename.toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
        } else emit updated();
        return;
}

void
MainWindow::saveCamera ( void )
{
        QString filename = QFileDialog::getSaveFileName ( this, tr ( "Save camera file to" ), ".", tr ( "CAM File (*.cam)" ) );
        if ( !this->_model.saveCamera ( filename.toStdString() ) ) {
                QString  message ( tr ( "Save failed." ) );
                statusBar()->showMessage ( message );
        }
        return;
}

void
MainWindow::polygon_wireframe ( void )
{
        this->_model.setRenderingMode ( WIRE );
        QString  message ( tr ( "Wireframe mode" ) );
        statusBar()->showMessage ( message );
        emit updated();
        return;
}

void
MainWindow::polygon_surface ( void )
{
        this->_model.setRenderingMode ( SURFACE );
        QString  message ( tr ( "Surface mode" ) );
        statusBar()->showMessage ( message );
        emit updated();
        return;
}

void
MainWindow::view_fit ( void )
{
        this->_model.viewFit();
        QString  message ( tr ( "View fit" ) );
        statusBar()->showMessage ( message );
        emit updated();
        return;
}

void
MainWindow::view_init ( void )
{
        this->_model.viewInit();
        QString  message ( tr ( "View init" ) );
        statusBar()->showMessage ( message );
        emit updated();
        return;
}

void
MainWindow::mouse_dragged ( float x, float y )
{
        QString  message ( tr ( "MouseDragging (" ) );
        QString strx;
        strx.setNum ( x );
        message += strx;
        message += tr ( ", " );
        QString stry;
        stry.setNum ( y );
        message += stry;
        message += tr ( ") " );
        statusBar()->showMessage ( message );
        return;

}


void 
MainWindow::saveSnapshot( void ){
        QString filename = QFileDialog::getSaveFileName ( this, tr ( "Save snapshot to" ), ".", tr ( "Image File (*.png)" ) );

	QImage image = this->_glwidget->grabFrameBuffer(true);
        if ( !image.save(filename, 0, 100)){
                QString  message ( tr ( "Save failed." ) );
                statusBar()->showMessage ( message );
        }
        return;
}
void 
MainWindow::update_surface_color(void) {
	QColor color = this->_colorWidget->getSurfaceColor();
	this->_model.setSurfaceColor ( color.red(),color.green(),color.blue() );
	emit updated();
}
