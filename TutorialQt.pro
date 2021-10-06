
QT = core gui widgets sql

DESTDIR = bin
TARGET = Agenda

OBJECTS_DIR = objs
MOC_DIR = moc_sources
UI_DIR  = ui_headers
RCC_DIR = res_sources

CONFIG -= debug_and_release

SOURCES += \
    main.cpp \
    JanelaPrincipal.cpp \
    Controle.cpp \
    Contato.cpp \
    ContatoDAO.cpp \
    JanelaContato.cpp

FORMS += \
    JanelaPrincipal.ui \
    JanelaContato.ui

HEADERS += \
    JanelaPrincipal.h \
    Controle.h \
    Contato.h \
    ContatoDAO.h \
    JanelaContato.h

RESOURCES += \
    icons.qrc

TRANSLATIONS += Dialeto.ts


# Win32 specific settings
win32 {
    QMAKE_TARGET_COMPANY = "Minicurso Qt"
    QMAKE_TARGET_PRODUCT = Agenda
    QMAKE_TARGET_DESCRIPTION = "Agenda do Minicurso"
    RC_ICONS = app_icon.ico
}
