#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T22:35:01
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarDealerShip
TEMPLATE = app


SOURCES += main.cpp\
        connetionform.cpp \
    authorizationform.cpp \
    mainform.cpp \
    addorderform.cpp \
    addneworderform.cpp \
    additemform.cpp

HEADERS  += connetionform.h \
    authorizationform.h \
    mainform.h \
    addorderform.h \
    addneworderform.h \
    additemform.h

FORMS    += connetionform.ui \
    authorizationform.ui \
    mainform.ui \
    addorderform.ui \
    addneworderform.ui \
    additemform.ui
