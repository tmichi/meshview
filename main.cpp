#include <QApplication>
#include <QDesktopWidget>
#include "Model.hpp"
#include "View.hpp"
#include "MainWindow.hpp"

int main ( int argc, char** argv )
{
        Model model;
        View view ( model );
        QApplication app ( argc, argv );

#if defined(Q_WS_MAC)
        // for Mac
        app.setWindowIcon ( QIcon ( ":/resources/meshview.icns" ) );
#else
        app.setWindowIcon ( QIcon ( ":/resources/meshview.ico" ) );
#endif

        MainWindow win ( model, view );

        win.show();
        return app.exec();
}
