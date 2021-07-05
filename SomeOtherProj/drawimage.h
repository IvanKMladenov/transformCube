#ifndef DRAWIMAGE_H
#define DRAWIMAGE_H

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QOpenGLShaderProgram>

//#include "mainwindow.h"

//#include "ui_mainwindow.h"

class DrawImage : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    DrawImage(QWidget *parent = nullptr);
    //DrawImage(MainWindow* meshVec, QWidget *parent = nullptr);
    ~DrawImage();
    void DramTheFuckingThing ();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();
private:
    void qColorToRgb(const QColor &C, float &r, float &g, float &b) const;
    float normalize_0_1(float val, float min, float max) const;
public:
     QOpenGLShaderProgram m_program;
private:
    //MainWindow * meshVectors;
    QOpenGLTexture *texture = nullptr;
    QQuaternion rotation;
    QMatrix4x4 projection;
};

#endif // DRAWIMAGE_H
