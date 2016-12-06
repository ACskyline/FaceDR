#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T17:05:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceDR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    facedetector.cpp \
    facerecognizer.cpp

HEADERS  += mainwindow.h \
    facerecognizer.h \
    facedetector.h

FORMS    += mainwindow.ui

INCLUDEPATH += . \
               ./include \

LIBS += ./libopencv_ts300.a \
        ./libopencv_calib3d300.dll.a \
        ./libopencv_core300.dll.a \
        ./libopencv_features2d300.dll.a \
        ./libopencv_flann300.dll.a \
        ./libopencv_hal300.a \
        ./libopencv_highgui300.dll.a \
        ./libopencv_imgcodecs300.dll.a \
        ./libopencv_imgproc300.dll.a \
        ./libopencv_ml300.dll.a \
        ./libopencv_objdetect300.dll.a \
        ./libopencv_photo300.dll.a \
        ./libopencv_shape300.dll.a \
        ./libopencv_stitching300.dll.a \
        ./libopencv_superres300.dll.a \
        ./libopencv_ts300.a \
        ./libopencv_video300.dll.a \
        ./libopencv_videoio300.dll.a \
        ./libopencv_videostab300.dll.a \

RESOURCES += \
    res.qrc
