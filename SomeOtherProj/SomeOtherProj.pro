HEADERS += \
    drawimage.h \
    inputvectors.h \
    mainwindow.h

SOURCES += \
    drawimage.cpp \
    inputvectors.cpp \
    main.cpp \
    mainwindow.cpp

QT += core gui widgets concurrent

FORMS += \
    mainwindow.ui

LIBS += -lopengl32
