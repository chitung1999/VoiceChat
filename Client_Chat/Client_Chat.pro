QT += quick core multimedia concurrent texttospeech

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/Controller.cpp \
        src/common/FileControl.cpp \
        src/common/TCPClient.cpp \
        src/main.cpp \
        src/model/MessageModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/Controller.h \
    src/common/AppEnum.h \
    src/common/Define.h \
    src/common/FileControl.h \
    src/common/TCPClient.h \
    src/model/MessageModel.h
