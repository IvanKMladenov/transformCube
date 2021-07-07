#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "drawimage.h"
//#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

    void editingFinished (const QString &string);

    void drawGeometry(QOpenGLShaderProgram *program);
    void doSomethingStupid ();

    const QVector3D *constData() const { return m_meshData.constData(); }

    //QVector<QVector3D> GetMesh() { return m_meshVec; }

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
    void initGeometry1Bad();
    void initGeometry();
    void initGeometryTest();
private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    QVector<QVector3D> m_inputData;
    QVector<QVector3D> m_meshData;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
