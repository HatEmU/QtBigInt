#
# Copyright (C) 2018-2019 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
           src

include($$PWD/tests/test.pri)

src.file = src/GMP.pro

gcc {
    SUBDIRS += tests
    tests.file = tests/tests.pro

}
