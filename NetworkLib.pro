TEMPLATE = app
CONFIG += console c++11
CONFIG += c++11
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lssl -lcrypto -lpthread

SOURCES += main.cpp \
    network.cpp \
    tcp.cpp \
    tcpsecure.cpp

HEADERS += \
    network.h \
    tcp.h \
    tcpsecure.h
