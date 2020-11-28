#-------------------------------------------------
#
# Project created by QtCreator 2020-11-27T22:06:16
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Library_Management
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utils/DatabaseConnection/DatabaseConnection.cpp \
    utils/ListPackage/Listt/Listt.cpp \
    utils/ListPackage/ArrayListt/ArrayListt.cpp \
    utils/ListPackage/LinkedListt/LinkedListt.cpp \
    utils/ListPackage/NodeLinkedListt/NodeLinkedListt.cpp \
    src/Publisher/Publisher.cpp \
    base/Repository/Repository.cpp \
    src/Publisher/PublisherRepository.cpp \
    src/Publisher/PublisherService.cpp \
    utils/Comparable/Comparable.cpp \
    src/Category/Category.cpp \
    src/Category/CategoryRepository.cpp \
    src/Category/CategoryService.cpp \
    utils/DotEnv/DotEnv.cpp

HEADERS  += mainwindow.h \
    utils/DatabaseConnection/DatabaseConnection.h \
    utils/ListPackage/Listt/Listt.h \
    utils/ListPackage/ArrayListt/ArrayListt.h \
    utils/ListPackage/LinkedListt/LinkedListt.h \
    utils/ListPackage/NodeLinkedListt/NodeLinkedListt.h \
    src/Publisher/Publisher.h \
    base/Repository/Repository.h \
    src/Publisher/PublisherRepository.h \
    src/Publisher/PublisherService.h \
    utils/Comparable/Comparable.h \
    src/Category/Category.h \
    src/Category/CategoryRepository.h \
    src/Category/CategoryService.h \
    utils/DotEnv/DotEnv.h

FORMS    += mainwindow.ui

DISTFILES += \
    config.txt
