#include "drawimage.h"
#include <iostream>

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

const float m_mesh[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

DrawImage::DrawImage (QWidget *parent)
    : QOpenGLWidget (parent)
{
    std::cout << "DrawImage c'tor" << std::endl;
}

//DrawImage::DrawImage ( QVector<float> meshVec, QWidget *parent)
//    : QOpenGLWidget (parent),
//      m_mesh(meshVec)
//{
//    std::cout << "DrawImage c'tor with mesh" << std::endl;
//}

DrawImage::~DrawImage() {
    cleanup();
}


//ivz - connect to mainwindow
void DrawImage::CallDraw()
{
  //  makeCurrent();
    std::cout << "CallDraw" << std::endl;
    this->paintGL();
}

void DrawImage::cleanup() {
    if (m_program == nullptr) {
        return;
    }
    //makeCurrent();
    m_meshVbo.destroy();
    delete m_program;
    m_program = nullptr;
    m_vao.destroy();
    //doneCurrent();
}

static const char* color3= "void main(void) {  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); }; ";

static const char* vertex3 = "attribute vec3 coordinates;\n void main(void) { gl_Position = vec4(coordinates, 1.0) ; \n gl_PointSize = 5.0; }";

GLuint DrawImage::initVBO() {
    //create vbo
    GLuint vbo;
    this->glGenBuffers(1, &vbo);
    this->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_mesh),m_mesh, GL_STATIC_DRAW);
    return  vbo;
}

GLuint DrawImage::initVAO() {
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    m_meshVbo.bind();

    int coordhnd = this ->glGetAttribLocation(m_program ->programId(), "coordinates");
    this ->glEnableVertexAttribArray(coordhnd);
    this ->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    return  0;
}

void DrawImage::initializeGL() {

    std::cout << "initializeGL" << std::endl;
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
 //   connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &DrawImage::cleanup);

    std::cout << "initializeGL after connect" << std::endl;
    initializeOpenGLFunctions();

    glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

    std::cout << "init shaders" << std::endl;
    auto vs = new QOpenGLShader(QOpenGLShader::Vertex);
    if (vs->compileSourceCode(vertex3)) {
        std::cout << "vs shader ok\r\n";
    } else {
        std::cout << "vs shader failed...\r\n";
    }

    auto ps = new QOpenGLShader(QOpenGLShader::Fragment);;
    if (ps->compileSourceCode(color3)) {
        std::cout << "ps shader ok\r\n";
    } else {
        std::cout << "ps shader failed...\r\n";
    }

    m_program = new QOpenGLShaderProgram(this);
    if (m_program ->addShader(vs)) {
        std::cout << "vs shader added ok\r\n";
    } else {
        qDebug() << "vs shader not added" << m_program->log();
    }

    if (m_program ->addShader(ps)) {
        std::cout << "ps shader added ok\r\n";
    } else {
        qDebug() << "ps shader not added" << m_program->log();
    }
    if (m_program ->link()) {
        std::cout << "linked vs and ps\r\n";
    } else {
        qDebug() << "failed to link ps and vs" << m_program->log();
    }

    if (m_program ->bind()) {
        qDebug() << "Success biding shader program";
    }

    auto hndvbo = initVBO();
//    std::cout << m_meshVbo.size() << "\r\n";
    //initVAO();
//    std::cout << m_meshVbo.size() << "\r\n";
    this->glBindBuffer(GL_ARRAY_BUFFER, hndvbo);
    int coordhnd = this->glGetAttribLocation(m_program ->programId(), "coordinates");
    //
    this->glVertexAttribPointer(coordhnd, 3, GL_FLOAT, GL_TRUE, 0, 0);
    this->glEnableVertexAttribArray(coordhnd);

//    m_program ->release();
}

void DrawImage::paintGL() {

    std::cout << "paintGL" << std::endl;

    this->glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    //int d = this->grabFramebuffer().depth();
    this->glEnable(GL_DEPTH_TEST);
    this->glDepthFunc(GL_LESS);

    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    std::cout << "paintGL enable plane options" << std::endl;
    this->glViewport(0, 0, 200, 200); //this->width(), this->height());

    //m_world.setToIdentity();
    //m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    //m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    //m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    //std::cout << "paintGL set world" << std::endl;

//    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
//   m_program ->bind();


    std::cout << "paintGL before glDrawArrays" << std::endl;
    //std::cout << m_mesh.size() << std::endl;
    //if(m_mesh.size() != 0) {
    this->glDrawArrays(GL_TRIANGLES, 0, 12*3);
        //glDrawElements(GL_TRIANGLE_STRIP, m_mesh.size(), GL_UNSIGNED_SHORT, &indexBuf);
    //}
   //ivz m_program ->release();
}

void DrawImage::resizeGL(int w, int h) {

    std::cout << "resizeGL" << std::endl;
   // this->glViewport(0, 0, w, h);
}
