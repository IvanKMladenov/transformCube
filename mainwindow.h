#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

//#include "drawimage.h"
//#include "ui_mainwindow.h"

class DrawImage;

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
    void addData (QVector<QStringRef>& data);

    const float *constData() const { return m_data.constData(); }

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
    void initGeometry();
    void initGeometryTest();
private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    QVector<QVector3D> m_inputData;
    QVector<QVector3D> m_meshData;
    QVector<GLfloat> m_data;
    GLshort *m_indexBuf;
    Ui::MainWindow *ui;


    DrawImage*  m_pglContext;
};

#endif // MAINWINDOW_H
