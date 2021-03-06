#-------------------------------------------------
#
# Project created by QtCreator 2019-08-30T09:44:49
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chatchat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    login.cpp \
    main_weight.cpp \
    group_list.cpp \
    delete_interface.cpp \
    friendinfo_interface.cpp \
    frilist.cpp \
    regroup_interface.cpp \
    chatroom.cpp \
    qnchatmessage.cpp \
    chatroom_plus.cpp \
    reg.cpp \
    ../utils/chat_proto.cpp \
    addfri_interface.cpp \
    info.cpp \
    repository.cpp \
    dialogrec.cpp \
    sliderdemo.cpp \
    group_chat.cpp \
    receive_addfri_interface.cpp

HEADERS += \
    login.h \
    main_weight.h \
    group_list.h \
    delete_interface.h \
    friendinfo_interface.h \
    frilist.h \
    regroup_interface.h \
    chatroom.h \
    qnchatmessage.h \
    chatroom_plus.h \
    reg.h \
    ../utils/chat_proto.h \
    addfri_interface.h \
    info.h \
    repository.h \
    my_include.h \
    dialogrec.h \
    sliderdemo.h \
    group_chat.h \
    receive_addfri_interface.h

FORMS += \
        chatchat.ui \
    login.ui \
    main_weight.ui \
    delete_interface.ui \
    friendinfo_interface.ui \
    frilist.ui \
    regroup_interface.ui \
    chatroom_plus.ui \
    reg.ui \
    addfri_interface.ui \
    info.ui \
    repository.ui \
    dialogrec.ui \
    sliderdemo.ui \
    group_chat.ui \
    receive_addfri_interface.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

LIBS += -ljsoncpp
