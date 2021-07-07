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
    DrawImage(QVector<QVector3D> meshVec, QWidget *parent = nullptr);
    //DrawImage(QVector<QVector3D> meshVec);
    ~DrawImage();
    //void DramTheFuckingThing ();
public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();
signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();
private:
    void qColorToRgb(const QColor &C, float &r, float &g, float &b) const;
    float normalize_0_1(float val, float min, float max) const;
private:
    void setupVertexAttribs();

    //new
    bool m_core;

    int m_xRot = 0;
    int m_yRot = 0;
    int m_zRot = 0;
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;

    QVector<QVector3D> m_mesh;

    QOpenGLBuffer m_meshVbo;
    QOpenGLVertexArrayObject m_vao;

    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    //old
    //QBasicTimer timer;
    QOpenGLShaderProgram *m_program = nullptr;
    //MainWindow *m_geometries = nullptr;

    //QOpenGLTexture *texture = nullptr;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};

#endif // DRAWIMAGE_H
