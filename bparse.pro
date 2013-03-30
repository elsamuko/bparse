TEMPLATE = app
CONFIG  += console
CONFIG  -= app_bundle
CONFIG  -= qt

DESTDIR     = bin
OBJECTS_DIR = .intermediate
MOC_DIR     = .intermediate
UI_DIR      = .intermediate
RCC_DIR     = .intermediate

INCLUDEPATH += src /opt/local/include/

SOURCES += src/main.cpp

HEADERS += \
    src/parser.h \
    src/mixer.h \
    src/generator.h

