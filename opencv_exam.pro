#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T15:12:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencv_exam
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    res.qrc

INCLUDEPATH += $$PWD/opencv_lib/android/include

LIBS += -L$$PWD/opencv_lib/android/libs/x86

#LIBS += -lopencv_calib3d
LIBS += -lopencv_core
#LIBS += -lopencv_features2d
#LIBS += -lopencv_flann
LIBS += -lopencv_highgui
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_imgproc
LIBS += -lopencv_java3
#LIBS += -lopencv_ml
#LIBS += -lopencv_objdetect
#LIBS += -lopencv_photo
#LIBS += -lopencv_shape
#LIBS += -lopencv_stitching
#LIBS += -lopencv_superres
#LIBS += -lopencv_video
#LIBS += -lopencv_videoio
#LIBS += -lopencv_videostab

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
