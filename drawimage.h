#ifndef DRAWIMAGE_H
#define DRAWIMAGE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "mainwindow.h"

//#include "ui_mainwindow.h"

class MainWindow;
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class DrawImage : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    DrawImage(QWidget *parent = nullptr);
    DrawImage(QVector<float> meshVec, QWidget *parent = nullptr);
    ~DrawImage();
public slots:
    //void setXRotation(int angle);
    //void setYRotation(int angle);
    //void setZRotation(int angle);
    void cleanup();
    void CallDraw(); // connect to draw button from mainwindow
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    //void createShaders();
    GLuint initVBO();
    GLuint initVAO();

    QOpenGLBuffer m_meshVbo;
    //QOpenGLBuffer indexBuf;

    QOpenGLVertexArrayObject m_vao;

    QOpenGLShaderProgram *m_program = nullptr;
};

#endif // DRAWIMAGE_H
