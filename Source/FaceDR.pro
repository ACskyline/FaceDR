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

LIBS += ./libopencv_calib3d300.dll \
        ./libopencv_ts300 \
        ./libopencv_core300.dll \
        ./libopencv_features2d300.dll \
        ./libopencv_flann300.dll \
        ./libopencv_hal300 \
        ./libopencv_highgui300.dll \
        ./libopencv_imgcodecs300.dll \
        ./libopencv_imgproc300.dll \
        ./libopencv_ml300 \
        ./libopencv_objdetect300.dll \
        ./libopencv_photo300.dll \
        ./libopencv_shape300.dll \
        ./libopencv_stitching300.dll \
        ./libopencv_superres300.dll \
        ./libopencv_video300.dll \
        ./libopencv_videoio300.dll \
        ./libopencv_videostab300.dll \

RESOURCES += \
    res.qrc

#win32: LIBS += -L$$PWD/./ -llibopencv_calib3d300.dll

#INCLUDEPATH += $$PWD/include
#DEPENDPATH += $$PWD/include

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./libopencv_calib3d300.dll.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/./liblibopencv_calib3d300.dll.a
