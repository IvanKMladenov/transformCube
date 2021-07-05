#ifndef INPUTVECTORS_H
#define INPUTVECTORS_H

#include <QWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
//#include <QFocusEvent>
//#include <QEvent>
//#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class InputVectors : public QWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit InputVectors(QWidget *parent = 0);
    virtual ~InputVectors();

    void editingFinished (const QString &string);

    void drawGeometry(QOpenGLShaderProgram *program);
    void doSomethingStupid ();

    QVector<QVector3D> GetMesh() { return meshVec; }

protected slots:
    bool eventFilter(QObject *obj, QEvent *event);
    void pushMeshVal1();
    void pushMeshVal2();
    void pushMeshVal3();
    void pushMeshVal4();
    void pushMeshVal5();
    void pushMeshVal6();
    void pushMeshVal7();
    void pushMeshVal8();
private:
    void initGeometry1();
    void initGeometry();
private:

    QVector<QVector3D> meshVec;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    Ui::MainWindow *ui;
};

#endif // INPUTVECTORS_H
