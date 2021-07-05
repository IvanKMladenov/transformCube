#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
//#include "inputvectors.h"
#include "drawimage.h"
//#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void editingFinished (const QString &string);

    void drawGeometry(QOpenGLShaderProgram *program);
    void doSomethingStupid ();

    QVector<QVector3D> GetMesh() { return m_meshVec; }

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
    //InputVectors* smtVec;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    DrawImage* glLogic;
    QVector<QVector3D> m_meshVec;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
