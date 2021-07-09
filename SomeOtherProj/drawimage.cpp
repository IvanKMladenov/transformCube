#include "drawimage.h"
#include <iostream>

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

DrawImage::DrawImage (QWidget *parent)
    : QOpenGLWidget (parent)
{
    m_mesh.resize(24 * sizeof(QVector3D));
    std::cout << "DrawImage c'tor" << std::endl;
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
}

DrawImage::DrawImage ( QVector<QVector3D> meshVec, QWidget *parent)
    : QOpenGLWidget (parent),
      m_mesh(meshVec)
{
    cleanup();
    m_mesh.resize(24 * sizeof(QVector3D));
    std::cout << "DrawImage c'tor with mesh" << std::endl;
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
}

//DrawImage::DrawImage(MainWindow* geometries)
//    : m_geometries(geometries)
//{
//}

DrawImage::~DrawImage() {
    cleanup();
}

void DrawImage::cleanup() {
    if (m_program == nullptr) {
        return;
    }
    makeCurrent();
    m_meshVbo.destroy();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
}

static void qNormalizeAngle(int &angle) {
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void DrawImage::setXRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void DrawImage::setYRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void DrawImage::setZRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

static const char *vertexShaderSourceCore =
    "#version 150\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "attribute vec3 normal;\n"
    "varying vec3 vert;\n"
    "varying vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying highp vec3 vert;\n"
    "varying highp vec3 vertNormal;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   gl_FragColor = vec4(col, 1.0);\n"
    "}\n";

void DrawImage::initializeGL() {

    std::cout << "initializeGL" << std::endl;
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &DrawImage::cleanup);

    std::cout << "initializeGL after connect" << std::endl;
    initializeOpenGLFunctions();

    float r, g, b, a = normalize_0_1(255.0f, 1.0f, 255.0f);
    qColorToRgb(Qt::green, r, g, b);
    glClearColor(r, g, b, a);

    std::cout << "init shaders" << std::endl;
    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    m_meshVbo.create();
    m_meshVbo.bind();
    m_meshVbo.allocate(m_mesh.constData(), m_mesh.size() * sizeof(QVector3D));

    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    // Light position is fixed.
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));


    m_program->release();
}

void DrawImage::setupVertexAttribs()
{
    m_meshVbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext() ->functions();
    f ->glEnableVertexAttribArray(0);
    //f ->glEnableVertexAttribArray(1);
    f ->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                             nullptr);
    //f ->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
    //                         reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_meshVbo.release();
}

void DrawImage::paintGL() {

    std::cout << "paintGL" << std::endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    std::cout << "paintGL enable plane options" << std::endl;

    m_world.setToIdentity();
    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    std::cout << "paintGL set world" << std::endl;

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();

    std::cout << "paintGL bind m_program" << std::endl;

    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

    std::cout << "paintGL before glDrawArrays" << std::endl;
    std::cout << m_mesh.size() << std::endl;
    if(m_mesh.size() != 0) {
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
        glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, &indexBuf);
    }
    m_program ->release();
}

void DrawImage::resizeGL(int w, int h) {

    std::cout << "resizeGL" << std::endl;
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void DrawImage::qColorToRgb(const QColor &C, float &r, float &g, float &b) const {
    r = normalize_0_1(C.red(), 1.0f, 255.0f);
    g = normalize_0_1(C.green(), 1.0f, 255.0f);
    b = normalize_0_1(C.blue(), 1.0f, 255.0f);
}

float DrawImage::normalize_0_1(float val, float min, float max) const
{
    return (val - min) / (max - min);
}
