#include "inputvectors.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QVector2D>
#include <QVector3D>

#include <iostream>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

InputVectors::InputVectors(QWidget *parent) :
    QWidget(parent),
    indexBuf(QOpenGLBuffer::IndexBuffer),
    ui(new Ui::MainWindow)
{
    //initializeOpenGLFunctions();
    arrayBuf.create();
    indexBuf.create();

    std::cout << "blq blq" << std::endl;

    ui ->setupUi(this);
    ui ->lineEdit_1 ->installEventFilter(this);
    ui ->lineEdit_2 ->installEventFilter(this);
    ui ->lineEdit_3 ->installEventFilter(this);
    ui ->lineEdit_4 ->installEventFilter(this);
    ui ->lineEdit_5 ->installEventFilter(this);
    ui ->lineEdit_6 ->installEventFilter(this);
    ui ->lineEdit_7 ->installEventFilter(this);
    ui ->lineEdit_8 ->installEventFilter(this);

    ui ->lineEdit_1 ->setText("Enter point e1");
    ui ->lineEdit_2 ->setText("Enter point e2");
    ui ->lineEdit_3 ->setText("Enter point e3");
    ui ->lineEdit_4 ->setText("Enter point e4");
    ui ->lineEdit_5 ->setText("Enter point e5");
    ui ->lineEdit_6 ->setText("Enter point e6");
    ui ->lineEdit_7 ->setText("Enter point e7");
    ui ->lineEdit_8 ->setText("Enter point e8");

     std::cout << "blq blq2" << std::endl;

    connect( ui ->lineEdit_1, SIGNAL(editingFinished()), this, SLOT(pushMeshVal1()));
    connect( ui ->lineEdit_2, SIGNAL(editingFinished()), this, SLOT(pushMeshVal2()));
    connect( ui ->lineEdit_3, SIGNAL(editingFinished()), this, SLOT(pushMeshVal3()));
    connect( ui ->lineEdit_4, SIGNAL(editingFinished()), this, SLOT(pushMeshVal4()));
    connect( ui ->lineEdit_5, SIGNAL(editingFinished()), this, SLOT(pushMeshVal5()));
    connect( ui ->lineEdit_6, SIGNAL(editingFinished()), this, SLOT(pushMeshVal6()));
    connect( ui ->lineEdit_7, SIGNAL(editingFinished()), this, SLOT(pushMeshVal7()));
    connect( ui ->lineEdit_8, SIGNAL(editingFinished()), this, SLOT(pushMeshVal8()));

    std::cout << "connects fineshed" << std::endl;

    //connect( ui ->draw, &QPushButton::pressed, this, &InputVectors::doSomethingStupid);
}

InputVectors::~InputVectors() {
    arrayBuf.destroy();
    indexBuf.destroy();
    delete ui;
}

void InputVectors::initGeometry1()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.

    std::cout << "initGeometry" << std::endl;

    VertexData vertices[] = {
        // Vertex data for face 0
        {meshVec[0], QVector2D(0.0f, 0.0f)},  // v0
        {meshVec[1], QVector2D(0.33f, 0.0f)}, // v1
        {meshVec[2], QVector2D(0.0f, 0.5f)},  // v2
        {meshVec[3], QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {meshVec[1], QVector2D( 0.0f, 0.5f)}, // v4
        {meshVec[4], QVector2D(0.33f, 0.5f)}, // v5
        {meshVec[3], QVector2D(0.0f, 1.0f)},  // v6
        {meshVec[5], QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {meshVec[4], QVector2D(0.66f, 0.5f)}, // v8
        {meshVec[6], QVector2D(1.0f, 0.5f)},  // v9
        {meshVec[5], QVector2D(0.66f, 1.0f)}, // v10
        {meshVec[7], QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {meshVec[6], QVector2D(0.66f, 0.0f)}, // v12
        {meshVec[0], QVector2D(1.0f, 0.0f)},  // v13
        {meshVec[7], QVector2D(0.66f, 0.5f)}, // v14
        {meshVec[2], QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {meshVec[6], QVector2D(0.33f, 0.0f)}, // v16
        {meshVec[4], QVector2D(0.66f, 0.0f)}, // v17
        {meshVec[0], QVector2D(0.33f, 0.5f)}, // v18
        {meshVec[1], QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {meshVec[2], QVector2D(0.33f, 0.5f)}, // v20
        {meshVec[3], QVector2D(0.66f, 0.5f)}, // v21
        {meshVec[7], QVector2D(0.33f, 1.0f)}, // v22
        {meshVec[5], QVector2D(0.66f, 1.0f)}  // v23
    };

     std::cout << "initGeometry after init vertices" << std::endl;

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
}

void InputVectors::initGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
//! [1]
}


void InputVectors::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    std::cout << "drawGeometry" << std::endl;

    initGeometry();

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);
}

void InputVectors::doSomethingStupid() {

    std::cout << "doSomethingStupid" << std::endl;

    for (int i = 0; i < meshVec.size(); ++i) {
        QString bb;
        &bb << meshVec[i];
        std::cout << bb.toStdString() << std::endl;
        ui ->debugWindow ->insertPlainText(bb);
    }
}

void InputVectors::pushMeshVal1() {
    auto smt = ui ->lineEdit_1 ->text().splitRef(QLatin1Char(','));
    QVector3D smtVec(smt[0].toFloat(), smt[1].toFloat(), smt[2].toFloat());
    //smtVec.normalize();
    meshVec.push_back(smtVec);
}

void InputVectors::pushMeshVal2() {
    auto smt = ui ->lineEdit_2 ->text().splitRef(QLatin1Char(','));
    QVector3D smtVec(smt[0].toFloat(), smt[1].toFloat(), smt[2].toFloat());
    //smtVec.normalize();
    meshVec.push_back(smtVec);
}

void InputVectors::pushMeshVal3() {
    auto smt = ui ->lineEdit_3 ->text().splitRef(QLatin1Char(','));
    QVector3D smtVec(smt[0].toFloat(), smt[1].toFloat(), smt[2].toFloat());
    //smtVec.normalize();
    meshVec.push_back(smtVec);
}

void InputVectors::pushMeshVal4() {
    auto smt = ui ->lineEdit_4 ->text().splitRef(QLatin1Char(','));
    QVector3D smtVec(smt[0].toFloat(), smt[1].toFloat(), smt[2].toFloat());
    //smtVec.normalize();
    meshVec.push_back(smtVec);
}

void InputVectors::pushMeshVal5() {
    auto smt = ui ->lineEdit_5 ->text().splitRef(QLatin1Char(','));
    QVector3D smtVec(smt[0].toFloat(), smt[1].toFloat(), smt[2].toFloat());
    //smtVec.normalize();
    meshVec.push_back(smtVec);
}

void InputVectors::pushMeshVal6() {
    auto smt = ui ->lineEdit_6 ->text().splitRef(QLatin1Char(','));
    QVector3D smtVec(smt[0].toFloat(), smt[1].toFloat(), smt[2].toFloat());
    //smtVec.normalize();
    meshVec.push_back(smtVec);
}

void InputVectors::pushMeshVal7() {
    auto smt = ui ->lineEdit_7 ->text().splitRef(QLatin1Char(','));
    QVector3D smtVec(smt[0].toFloat(), smt[1].toFloat(), smt[2].toFloat());
    //smtVec.normalize();
    meshVec.push_back(smtVec);
}

void InputVectors::pushMeshVal8() {
    auto smt = ui ->lineEdit_8 ->text().splitRef(QLatin1Char(','));
    QVector3D smtVec(smt[0].toFloat(), smt[1].toFloat(), smt[2].toFloat());
    //smtVec.normalize();
    meshVec.push_back(smtVec);
}

bool InputVectors::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui ->lineEdit_1) {
        if (event ->type() == QEvent::FocusIn) {
            ui ->lineEdit_1 ->setText("");
        //} else if (event ->type() == QEvent::FocusOut) {
        //    QString smt = ui ->lineEdit_1 ->text();
        //    ui ->lineEdit_1 ->setText("kurac22");
        }
    }
    if (watched == ui ->lineEdit_2) {
        if (event ->type() == QEvent::FocusIn) {
            ui ->lineEdit_2 ->setText("");
        //} else if (event ->type() == QEvent::FocusOut) {
        //    ui ->lineEdit_2 ->setText("kurac22");
        }
    }
    if (watched == ui ->lineEdit_3) {
        if (event ->type() == QEvent::FocusIn) {
             ui ->lineEdit_3 ->setText("");
        //} else if (event ->type() == QEvent::FocusOut) {
        //     ui ->lineEdit_3 ->setText("kurac22");
        }
    }
    if (watched == ui ->lineEdit_4) {
        if (event ->type() == QEvent::FocusIn) {
             ui ->lineEdit_4 ->setText("");
        //} else if (event ->type() == QEvent::FocusOut) {
        //     ui ->lineEdit_4 ->setText("kurac22");
        }
    }
    if (watched == ui ->lineEdit_5) {
        if (event ->type() == QEvent::FocusIn) {
             ui ->lineEdit_5 ->setText("");
        //} else if (event ->type() == QEvent::FocusOut) {
        //     ui ->lineEdit_5 ->setText("kurac22");
        }
    }
    if (watched == ui ->lineEdit_6) {
        if (event ->type() == QEvent::FocusIn) {
             ui ->lineEdit_6 ->setText("");
        //} else if (event ->type() == QEvent::FocusOut) {
        //     ui ->lineEdit_6 ->setText("kurac22");
        }
    }
    if (watched == ui ->lineEdit_7) {
        if (event ->type() == QEvent::FocusIn) {
             ui ->lineEdit_7 ->setText("");
        //} else if (event ->type() == QEvent::FocusOut) {
        //     ui ->lineEdit_7 ->setText("kurac22");
        }
    }
    if (watched == ui ->lineEdit_8) {
        if (event ->type() == QEvent::FocusIn) {
             ui ->lineEdit_8 ->setText("");
        //} else if (event ->type() == QEvent::FocusOut) {
        //     ui ->lineEdit_8 ->setText("kurac22");
        }
    }
    return QWidget::eventFilter(watched,event);
}
