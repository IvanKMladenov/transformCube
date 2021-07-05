#include "drawimage.h"
#include <iostream>

DrawImage::DrawImage (QWidget *parent)
    : QOpenGLWidget (parent)
{
    std::cout << "DrawImage c'tor" << std::endl;
}

//DrawImage::DrawImage(MainWindow* meshVec, QWidget *parent)
//    : QOpenGLWidget (parent),
//      meshVectors(meshVec)
//{
//}

DrawImage::~DrawImage() {
    makeCurrent();
    delete texture;
    //delete meshVectors;
    doneCurrent();
}

void DrawImage::initializeGL() {

    std::cout << "initializeGL" << std::endl;

    float r, g, b, a = normalize_0_1(255.0f, 1.0f, 255.0f);
    initializeOpenGLFunctions();
    qColorToRgb(Qt::red, r, g, b);
    glClearColor(r, g, b, a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    std::cout << "init shaders" << std::endl;
    initShaders();
    //initTextures();

    // Use QBasicTimer because its faster than QTimer
    //timer.start(12, this);
}

void DrawImage::initShaders() {

    std::cout << "initShaders" << std::endl;

    const char *vsrc =
            "uniform mat4 mvp_matrix;\n"
            "attribute vec4 a_position;\n"
            "attribute vec2 a_texcoord;\n"
            "varying vec2 v_texcoord;\n"
            "void main()  \n"
            "{   \n"
            "  gl_Position = mvp_matrix * a_position;          \n"
            "  v_texcoord = a_texcoord; \n"
            "} \n";

    const char *fsrc =
            "uniform mediump vec4 color; \n"
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = color;\n"
            "}\n";

    m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vsrc);
    m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fsrc);

    m_program.bindAttributeLocation("a_position", 0);
    m_program.bindAttributeLocation("a_Color", 1);

    m_program.link();
    m_program.bind();

}

void DrawImage::initTextures() {
    // Load cube.png image
    //texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture ->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture ->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture ->setWrapMode(QOpenGLTexture::Repeat);
}

void DrawImage::paintGL() {

    std::cout << "paintGL" << std::endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QColor color(0, 255, 0, 255);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    m_program.setUniformValue("mvp_matrix", projection * matrix);

    // Use texture unit 0 which contains cube.png
    m_program.setUniformValue(m_program.uniformLocation("color"), color);

    // Draw cube geometry
    std::cout << "ba li mu mamata" << std::endl;
    //meshVectors ->drawGeometry(&m_program);

}

void DrawImage::resizeGL(int w, int h) {

    std::cout << "resizeGL" << std::endl;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MATRIX_MODE);
    glLoadIdentity();

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    //// Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
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
