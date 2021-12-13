TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += gui
QT += widgets
QT += opengl
QT += core

SOURCES += main.cpp \
    mainwindow.cpp \
    reserve.cpp \
    cameradoppia.cpp \
    contenitore.cpp \
    hotel.cpp \
    camerasingola.cpp \
    prenotazione.cpp \
    reservations.cpp \
    royalsuite.cpp \
    stanza.cpp \
    struttura.cpp \
    suite.cpp

HEADERS += \
    mainwindow.h \
    reserve.h \
    cameradoppia.h \
    contenitore.h \
    hotel.h \
    camerasingola.h \
    prenotazione.h \
    reservations.h \
    royalsuite.h \
    stanza.h \
    struttura.h \
    suite.h

