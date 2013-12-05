#-------------------------------------------------
#
# Project created by QtCreator 2013-12-04T20:42:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GeneticRoutes
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/FlightControlSystem.cpp \
    src/DataAccess/DataRepository.cpp \
    src/DataAccess/Constants.cpp \
    src/Models/Target.cpp \
    src/Models/Route.cpp \
    src/Models/FlightBase.cpp \
    src/Models/Drone.cpp \
    src/Models/Coordinates.cpp \
    src/RouteManager/RouteManager.cpp \
    src/RouteManager/Models/Population.cpp \
    src/RouteManager/Models/Gene.cpp \
    src/RouteManager/Models/Chromosome.cpp \
    src/Utils/TargetCoordinator.cpp \
    basesdialog.cpp \
    targetsdialog.cpp \
    dronesdialog.cpp

HEADERS  += mainwindow.h \
    src/DataAccess/DataRepository.h \
    src/DataAccess/Constants.h \
    src/Models/Target.h \
    src/Models/Route.h \
    src/Models/FlightBase.h \
    src/Models/Drone.h \
    src/Models/Coordinates.h \
    src/RouteManager/RouteManager.h \
    src/RouteManager/Models/Population.h \
    src/RouteManager/Models/Gene.h \
    src/RouteManager/Models/Chromosome.h \
    src/Utils/TargetCoordinator.h \
    basesdialog.h \
    targetsdialog.h \
    dronesdialog.h

FORMS    += mainwindow.ui \
    basesdialog.ui \
    targetsdialog.ui \
    dronesdialog.ui
