#
# Copyright (C) 2018-2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#


QT       -= core gui

TARGET = MiniGMP
TEMPLATE = lib

DEFINES += MINIGMP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

TARGET = QtBigInt

CONFIG += static

CONFIG(release, debug|release): {
    DESTDIR="$$PWD/build/release"
} else {
    DESTDIR="$$PWD/build/debug"
}

DISTFILES += \
    README \

HEADERS += \
    bigint.h \
    mini-gmp.h \
    minigmp_global.h

SOURCES += \
    bigint.cpp \
    mini-gmp.c
