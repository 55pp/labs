TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS+=-pg
QMAKE_LFLAGS+=-pg

SOURCES += main.cpp \
    menustring.cpp \
    entity.cpp \
    dummy.cpp \
    player.cpp \
    movestate.cpp \
    idlestate.cpp \
    fallstate.cpp \
    jumpstate.cpp \
    shootstate.cpp \
    level.cpp \
    view.cpp \
    entytiiterator.cpp \
    bullet.cpp \
    vectorentity.cpp \
    modifications.cpp \
    decorator.cpp \
    modspeed.cpp \
    modcolor.cpp \
    loot.cpp \
    lootbox.cpp \
    coin.cpp \
    listentities.cpp \
    renderwindow.cpp \
    renderconsole.cpp \
    inspector.cpp \
    playeridle.cpp \
    ianimation.cpp \
    bulletmodel.cpp \
    enemy.cpp \
    modbigboy.cpp \
    factorymethod.cpp \
    simpleenemy.cpp \
    redenemy.cpp \
    gun.cpp \
    bigenemy.cpp \
    npc.cpp \
    bignpc.cpp \
    abstractfactory.cpp \
    simplefactory.cpp \
    bigfactory.cpp \
    bulletspool.cpp \
    bulletbuilder.cpp \
    firebullet.cpp \
    bulletconstructor.cpp \
    memento.cpp \
    commandrestart.cpp \
    operation.cpp \
    playsound.cpp \
    inputhandler.cpp \
    makesavecommand.cpp \
    dropcoinuntildie.cpp \
    flyenemy.cpp \
    flyidle.cpp \
    flyaction.cpp \
    chain.cpp \
    blockidle.cpp \
    blockattack.cpp \
    blockremove.cpp \
    strategy.cpp \
    simplefly.cpp \
    zigzagfly.cpp \
    mediator.cpp \
    healthmediator.cpp

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system


HEADERS += \
    menustring.h \
    entity.h \
    dummy.h \
    player.h \
    ianimation.h \
    playeridle.h \
    playermove.h \
    playerjump.h \
    playerfall.h \
    command.h \
    inputhandler.h \
    state.h \
    jumpstate.h \
    movestate.h \
    idlestate.h \
    fallstate.h \
    playershoot.h \
    shootstate.h \
    enemyidle.h \
    onlyidle.h \
    level.h \
    view.h \
    entytiiterator.h \
    bullet.h \
    bulletmove.h \
    vectorentity.h \
    modspeed.h \
    modifications.h \
    decorator.h \
    modcolor.h \
    loot.h \
    lootbox.h \
    coin.h \
    lootboxidle.h \
    listentities.h \
    bridge.h \
    renderwindow.h \
    renderconsole.h \
    inspector.h \
    bulletmodel.h \
    enemy.h \
    modbigboy.h \
    factorymethod.h \
    simpleenemy.h \
    redenemy.h \
    gun.h \
    bigenemy.h \
    npc.h \
    bignpc.h \
    abstractfactory.h \
    simplefactory.h \
    bigfactory.h \
    bulletspool.h \
    bulletbuilder.h \
    firebullet.h \
    bulletconstructor.h \
    memento.h \
    commandrestart.h \
    operation.h \
    playsound.h \
    makesavecommand.h \
    dropcoinuntildie.h \
    flyenemy.h \
    flyidle.h \
    flyaction.h \
    chain.h \
    blockidle.h \
    blockattack.h \
    blockremove.h \
    strategy.h \
    simplefly.h \
    zigzagfly.h \
    mediator.h \
    healthmediator.h

INCLUDEPATH += /home/konstantin/QtProjects/Pattern/src/
DEPENDPATH += /home/konstantin/QtProjects/Pattern/src/

DISTFILES +=
