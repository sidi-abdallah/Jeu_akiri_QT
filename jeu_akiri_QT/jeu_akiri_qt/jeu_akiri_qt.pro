QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/AkariModel.cpp\
    src/AkariView.cpp \
    src/Cell.cpp \
    src/main.cpp\
    src/mainwindow.cpp \
    src/Grid.cpp \
#    src/states/State.cpp \
#    src/states/FullBlackState.cpp \
#    src/states/ZeroBlackState.cpp \
#    src/states/OneBlackState.cpp \
#    src/states/TwoBlackState.cpp \
#    src/states/ThreeBlackState.cpp \
#    src/states/FourBlackState.cpp \
#    src/states/UnenlightenedState.cpp \
#    src/states/EnlightenedState.cpp \
#    src/states/YellowLampState.cpp \
#    src/states/RedLampState.cpp \








HEADERS += \
    include/AkariModel.h \
    include/common.h \
    include/mainwindow.h \
    include/AkariView.h \
    include/Matrix.h \
    include/Cell.h \
    include/Grid.h \
#    include/states/State.h \
#    include/states/FullBlackState.h \
#    include/states/ZeroBlackState.h \
#    include/states/OneBlackState.h \
#    include/states/TwoBlackState.h \
#    include/states/ThreeBlackState.h \
#    include/states/FourBlackState.h \
#    include/states/UnenlightenedState.h \
#    include/states/EnlightenedState.h \
#    include/states/YellowLampState.h \
#    include/states/RedLampState.h \



FORMS += \
    mainwindow.ui


TRANSLATIONS += \
    jeu_akiri_qt_fr_FR.ts


QT += printsupport

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ds_digital/digital_font.qrc \
    grids.qrc \
    icons/icons.qrc
