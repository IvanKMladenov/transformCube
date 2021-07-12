#include <QApplication>
#include <QSurfaceFormat>

#include "mainwindow.h"
//#include "inputvectors.h"
//#include "drawimage.h"

int main (int argc, char *argv[]){

    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    //InputVectors smt;
    //DrawImage smt;
    MainWindow smt;
    //smt.resize(800,600);
    smt.show();
    return app.exec();
}
