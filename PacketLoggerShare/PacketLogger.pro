QT += core gui network widgets  # Removed ui-tools

TARGET = PacketLogger
TEMPLATE = lib  # Changed from 'app' to 'lib'

CONFIG += c++17
CONFIG += qt

# Ensure correct Qt version is used
QMAKE_QT_VERSION = 5



SOURCES += \
    AddressFunctions.cpp \
    AddressManager.cpp \
    AdvancedGroupBox.cpp \
    AdvancedListWidget.cpp \
    Config.cpp \
    DamageCounterUI.cpp \
    FilterUI.cpp \
    HookFunctions.cpp \
    HookManager.cpp \
    Memory.cpp \
    PacketSenderUI.cpp \
    PacketUI.cpp \
    TcpServer.cpp \
    WhitelistSettingsUI.cpp \
    main.cpp

HEADERS += \
    AddressFunctions.h \
    AddressManager.h \
    AdvancedGroupBox.h \
    AdvancedListWidget.h \
    Config.h \
    Defines.h \
    DamageCounterUI.h \
    FilterUI.h \
    HookFunctions.h \
    HookManager.h \
    Memory.h \
    PacketSenderUI.h \
    PacketUI.h \
    TcpServer.h \
    WhitelistSettingsUI.h \
    Typedef.h

FORMS += \
    DamageCounterUI.ui \
    FilterUI.ui \
    PacketSenderUI.ui \
    WhitelistSettingsUI.ui \
    PacketUI.ui

INCLUDEPATH += \
    C:/Qt/5.15.2/msvc2019/include \
    C:/Qt/5.15.2/msvc2019/include/QtCore \
    C:/Qt/5.15.2/msvc2019/include/QtNetwork \
    C:/Qt/5.15.2/msvc2019/include/QtWidgets \
    C:/Qt/5.15.2/msvc2019/include/QtGui \
    C:/vcpkg/vcpkg/installed/x86-windows-static/include

QMAKE_CXXFLAGS += -Wall

CONFIG += moc