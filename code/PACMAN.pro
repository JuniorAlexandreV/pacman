QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Definir diretórios para MOC e OBJ
MOC_DIR = moc
OBJECTS_DIR = obj

# Incluir fontes, cabeçalhos e arquivos de formulário
SOURCES += \
    Fantasma.cpp \
    GameScene.cpp \
    PacMan.cpp \
    Personagem.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Fantasma.h \
    GameScene.h \
    PacMan.h \
    Personagem.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Regras de implantação padrão
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
