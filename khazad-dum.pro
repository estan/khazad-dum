TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lreadline

SOURCES += main.cpp \
    Item.cpp \
    Actor.cpp \
    Player.cpp \
    Game.cpp \
    Balrog.cpp \
    Environment.cpp \
    Exit.cpp \
    Room.cpp \
    Swamp.cpp \
    Door.cpp \
    Random.cpp \
    Portal.cpp \
    Bridge.cpp \
    Enemy.cpp \
    Wizard.cpp \
    Dwarf.cpp \
    Elf.cpp \
    Goblin.cpp \
    Orc.cpp \
    Input.cpp \
    NocturnalDoor.cpp \
    HiddenDoor.cpp \
    LockedDoor.cpp

HEADERS += \
    Item.h \
    Actor.h \
    Player.h \
    Game.h \
    Balrog.h \
    Environment.h \
    Exit.h \
    Room.h \
    Swamp.h \
    Door.h \
    Random.h \
    Portal.h \
    Bridge.h \
    Enemy.h \
    Wizard.h \
    Dwarf.h \
    Elf.h \
    Print.h \
    Goblin.h \
    Orc.h \
    Input.h \
    NocturnalDoor.h \
    HiddenDoor.h \
    LockedDoor.h

TEXT_SOURCES += \
    Game.txt.in

textprocessor.input = TEXT_SOURCES
textprocessor.output = ${QMAKE_FILE_BASE}
textprocessor.commands = sed \"s,$${LITERAL_HASH}.*,,\" ${QMAKE_FILE_NAME} > ${QMAKE_FILE_OUT}
textprocessor.CONFIG += no_link target_predeps

QMAKE_EXTRA_COMPILERS += textprocessor
