#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
//ivz include the drawer here
#include "drawimage.h"

MainWindow::MainWindow() :
    indexBuf(QOpenGLBuffer::IndexBuffer),
    ui(new Ui::MainWindow)
{
    std::cout << "MainWindow c'tor call" << std::endl;
    ui ->setupUi(this);

#if 0 //why is this installing event???
    ui ->lineEdit_1 ->installEventFilter(this);
    ui ->lineEdit_2 ->installEventFilter(this);
    ui ->lineEdit_3 ->installEventFilter(this);
    ui ->lineEdit_4 ->installEventFilter(this);
    ui ->lineEdit_5 ->installEventFilter(this);
    ui ->lineEdit_6 ->installEventFilter(this);
    ui ->lineEdit_7 ->installEventFilter(this);
    ui ->lineEdit_8 ->installEventFilter(this);
#endif
    //ui ->lineEdit_1 ->setText("Enter point e1");
    //ui ->lineEdit_2 ->setText("Enter point e2");
    //ui ->lineEdit_3 ->setText("Enter point e3");
    //ui ->lineEdit_4 ->setText("Enter point e4");
    //ui ->lineEdit_5 ->setText("Enter point e5");
    //ui ->lineEdit_6 ->setText("Enter point e6");
    //ui ->lineEdit_7 ->setText("Enter point e7");
    //ui ->lineEdit_8 ->setText("Enter point e8");

    std::cout << "MainWindow init LineEdits" << std::endl;

    connect( ui ->lineEdit_1, SIGNAL(editingFinished()), this, SLOT(pushMeshVal1()));
    connect( ui ->lineEdit_2, SIGNAL(editingFinished()), this, SLOT(pushMeshVal2()));
    connect( ui ->lineEdit_3, SIGNAL(editingFinished()), this, SLOT(pushMeshVal3()));
    connect( ui ->lineEdit_4, SIGNAL(editingFinished()), this, SLOT(pushMeshVal4()));
    connect( ui ->lineEdit_5, SIGNAL(editingFinished()), this, SLOT(pushMeshVal5()));
    connect( ui ->lineEdit_6, SIGNAL(editingFinished()), this, SLOT(pushMeshVal6()));
    connect( ui ->lineEdit_7, SIGNAL(editingFinished()), this, SLOT(pushMeshVal7()));
    connect( ui ->lineEdit_8, SIGNAL(editingFinished()), this, SLOT(pushMeshVal8()));

    std::cout << "MainWindow connect LineEdits" << std::endl;

    initGeometryTest();


    m_pglContext = ui->openGLWidget; //new DrawImage(this);


//    m_pglContext ->setMouseTracking(true);


    connect(ui->draw, SIGNAL(clicked()), this->m_pglContext, SLOT(CallDraw()));
}

MainWindow::~MainWindow() {
    arrayBuf.destroy();
    indexBuf.destroy();
    delete ui;
}

void MainWindow::initGeometryTest() {
    std::cout << "initGeometryTest" << std::endl;
    //m_inputData.push_back(QVector3D(-1, -1, 1)); //0
    //m_inputData.push_back(QVector3D(1, -1, 1)); //1
    //m_inputData.push_back(QVector3D(-1, 1, 1)); //2
    //m_inputData.push_back(QVector3D(1, 1, 1)); //3
    //m_inputData.push_back(QVector3D(1, -1, -1)); //4
    //m_inputData.push_back(QVector3D(1, 1, -1)); //5
    //m_inputData.push_back(QVector3D(-1, -1, -1)); //6
    //m_inputData.push_back(QVector3D(-1, 1, -1)); //7

    const float triangleArray[] = {
        //face1
        -0.5f, -0.5f, 1.0f,// 1.0f,//position
        0.5f, -0.5f, 1.0f, //1.0f,//position
        0.5f, 0.5f, 1.0f, //1.0f,//position
        -0.5f, 0.5f, 1.0f//, 1.0f//position
        //face2
        //1.0f,   -1.0f,  1.0f, 1.0f,//color
        //1.0f,   -1.0f, -1.0f, 1.0f,//color
        //1.0f,    1.0f,  1.0f, 1.0f,//color
        //1.0f,    1.0f,  -1.0f, 1.0f,//color
        //color1
        //1.0f,    0.5f, 0.0f, 1.0f,//color
        //1.0f,    0.0f, 0.0f, 1.0f,//color
        //1.0f,    1.0f, 0.0f, 1.0f,//color
        //1.0f,    0.0f, 1.0f, 1.0f,//color
        //color2
        //1.0f,    0.5f, 0.0f, 1.0f,//color
        //1.0f,    0.0f, 0.0f, 1.0f,//color
        //1.0f,    1.0f, 0.0f, 1.0f,//color
        //1.0f,    0.0f, 1.0f, 1.0f//color
    };

    for (int i = 0; i < 12; ++i) {
        m_data.push_back(triangleArray[i]);
    }

    // Vertex data for face 0
    // Vertex data for face 0
    //m_meshData.push_back(QVector3D(-0.1f, -0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(0.1f, -0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(-0.1f, 0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(0.1f, 0.1f, 0.1f)); //ready
    //
    //// Vertex color for face 0
    //m_meshData.push_back(QVector3D(1.0f, 0.5f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 1.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));

    //Vertex data for face 1
    //m_meshData.push_back(QVector3D(0.1f, -0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(0.1f, -0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(0.1f, 0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(0.1f, 0.1f, -0.1f));   //ready
    //
    //// Vertex color for face 1
    //m_meshData.push_back(QVector3D(1.0f, 0.5f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 1.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //
    //// Vertex data for face 2
    //m_meshData.push_back(QVector3D(0.1f, -0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(-0.1f, -0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(0.1f, 0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(-0.1f, 0.1f, -0.1f));   //ready
    //
    //// Vertex color for face 2
    //m_meshData.push_back(QVector3D(1.0f, 0.5f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 1.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //
    //// Vertex data for face 3
    //m_meshData.push_back(QVector3D(-0.1f, -0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(-0.1f, -0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(-0.1f, 0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(-0.1f, 0.1f, 0.1f));   //ready
    //
    //// Vertex color for face 3
    //m_meshData.push_back(QVector3D(1.0f, 0.5f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 1.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //
    //// Vertex data for face 4
    //m_meshData.push_back(QVector3D(-0.1f, -0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(0.1f, -0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(-0.1f, -0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(0.1f, -0.1f, 0.1f));   //ready
    //
    //// Vertex color for face 4
    //m_meshData.push_back(QVector3D(1.0f, 0.5f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 1.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //
    //// Vertex data for face 5
    //m_meshData.push_back(QVector3D(-0.1f, 0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(0.1f, 0.1f, 0.1f));
    //m_meshData.push_back(QVector3D(-0.1f, 0.1f, -0.1f));
    //m_meshData.push_back(QVector3D(0.1f, 0.1f, -0.1f));
    //
    //// Vertex color for face 5
    //m_meshData.push_back(QVector3D(1.0f, 0.5f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 1.0f, 1.0f));
    //m_meshData.push_back(QVector3D(1.0f, 0.0f, 1.0f));
}

/*
void MainWindow::initGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.

    std::cout << "initGeometry" << std::endl;

    VertexData vertices[] = {
        // Vertex data for face 0
        {m_inputData[0], QVector2D(0.0f, 0.0f)},  // v0
        {m_inputData[1], QVector2D(0.33f, 0.0f)}, // v1
        {m_inputData[2], QVector2D(0.0f, 0.5f)},  // v2
        {m_inputData[3], QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {m_inputData[1], QVector2D( 0.0f, 0.5f)}, // v4
        {m_inputData[4], QVector2D(0.33f, 0.5f)}, // v5
        {m_inputData[3], QVector2D(0.0f, 1.0f)},  // v6
        {m_inputData[5], QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {m_inputData[4], QVector2D(0.66f, 0.5f)}, // v8
        {m_inputData[6], QVector2D(1.0f, 0.5f)},  // v9
        {m_inputData[5], QVector2D(0.66f, 1.0f)}, // v10
        {m_inputData[7], QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {m_inputData[6], QVector2D(0.66f, 0.0f)}, // v12
        {m_inputData[0], QVector2D(1.0f, 0.0f)},  // v13
        {m_inputData[7], QVector2D(0.66f, 0.5f)}, // v14
        {m_inputData[2], QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {m_inputData[6], QVector2D(0.33f, 0.0f)}, // v16
        {m_inputData[4], QVector2D(0.66f, 0.0f)}, // v17
        {m_inputData[0], QVector2D(0.33f, 0.5f)}, // v18
        {m_inputData[1], QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {m_inputData[2], QVector2D(0.33f, 0.5f)}, // v20
        {m_inputData[3], QVector2D(0.66f, 0.5f)}, // v21
        {m_inputData[7], QVector2D(0.33f, 1.0f)}, // v22
        {m_inputData[5], QVector2D(0.66f, 1.0f)}  // v23
    };

     //std::cout << "initGeometry after init vertices" << std::endl;

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    //GLushort indices[] = {
    //     0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    //     4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
    //     8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
    //    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
    //    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
    //    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    //};

    // Transfer vertex data to VBO 0
    //arrayBuf.bind();
    //arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    //indexBuf.bind();
    //indexBuf.allocate(indices, 34 * sizeof(GLushort));
}
*/
//void MainWindow::drawGeometry(QOpenGLShaderProgram *program)
//{
//    std::cout << "drawGeometry" << std::endl;
//    // Tell OpenGL which VBOs to use
//    arrayBuf.bind();
//    indexBuf.bind();
//
//    // Offset for position
//    quintptr offset = 0;
//
//    // Tell OpenGL programmable pipeline how to locate vertex position data
//    int vertexLocation = program ->attributeLocation("a_position");
//    std::cout << vertexLocation << std::endl;
//    program ->enableAttributeArray(vertexLocation);
//    program ->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
//
//    // Offset for texture coordinate
//    offset += sizeof(QVector3D);
//
//    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    int texcoordLocation = program->attributeLocation("a_texcoord");
//    std::cout << texcoordLocation << std::endl;
//    program ->enableAttributeArray(texcoordLocation);
//    program ->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
//
//    // Draw cube geometry using indices from VBO 1
//    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);
//}

void MainWindow::addData (QVector<QStringRef>& data) {
    std::cout << "addData" << std::endl;
    std::cout << data[0].toString().toStdString() << std::endl;
    std::cout << data[1].toString().toStdString() << std::endl;
    std::cout << data[2].toString().toStdString() << std::endl;

    QVector3D smtVec(data[0].toFloat(), data[1].toFloat(), data[2].toFloat());
    smtVec.normalize();
    //m_inputData.push_back(smtVec);
}

void MainWindow::pushMeshVal1() {
    std::cout << "pushMeshVal1" << std::endl;
    if (!ui ->lineEdit_1 ->text().isEmpty()) {
        auto smt = ui ->lineEdit_1 ->text().splitRef(QLatin1Char(','));
        addData(smt);
    }
}

void MainWindow::pushMeshVal2() {
    std::cout << "pushMeshVal2" << std::endl;
    if (!ui ->lineEdit_2 ->text().isEmpty()) {
        auto smt = ui ->lineEdit_2 ->text().splitRef(QLatin1Char(','));
        addData(smt);
    }
}

void MainWindow::pushMeshVal3() {
    std::cout << "pushMeshVal3" << std::endl;
    if (!ui ->lineEdit_3 ->text().isEmpty()) {
        auto smt = ui ->lineEdit_3 ->text().splitRef(QLatin1Char(','));
        addData(smt);
    }
}

void MainWindow::pushMeshVal4() {
    std::cout << "pushMeshVal4" << std::endl;
    if (!ui ->lineEdit_4 ->text().isEmpty()) {
        auto smt = ui ->lineEdit_4 ->text().splitRef(QLatin1Char(','));
        addData(smt);
    }
}

void MainWindow::pushMeshVal5() {
    std::cout << "pushMeshVal5" << std::endl;
    if (!ui ->lineEdit_5 ->text().isEmpty()) {
        auto smt = ui ->lineEdit_5 ->text().splitRef(QLatin1Char(','));
        addData(smt);
    }
}

void MainWindow::pushMeshVal6() {
    std::cout << "pushMeshVal6" << std::endl;
    if (!ui ->lineEdit_6 ->text().isEmpty()) {
        auto smt = ui ->lineEdit_6 ->text().splitRef(QLatin1Char(','));
        addData(smt);
    }
}

void MainWindow::pushMeshVal7() {
    std::cout << "pushMeshVal7" << std::endl;
    if (!ui ->lineEdit_7 ->text().isEmpty()) {
        auto smt = ui ->lineEdit_7 ->text().splitRef(QLatin1Char(','));
        addData(smt);
    }
}

void MainWindow::pushMeshVal8() {
    std::cout << "pushMeshVal8" << std::endl;
    if (!ui ->lineEdit_8 ->text().isEmpty()) {
        auto smt = ui ->lineEdit_8 ->text().splitRef(QLatin1Char(','));
        addData(smt);
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
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
