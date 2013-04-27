#-------------------------------------------------
#
# Project created by QtCreator 2013-04-27T19:01:24
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphal_gui
TEMPLATE = app
INCLUDEPATH += ../libgraphal/ ../libgraphal/generated/
CONFIG += qt thread warn_on
DEFINES += QTGUI
RC_FILE = graphal_gui.rc
ICON = images/toast/toast.icns
LIBS += -L$$PWD/../build/dist/ -lgraphal

# Allow load libgraphal.so from the same directory where the binary is stored
QMAKE_LFLAGS += "-Wl,-rpath,'\$$ORIGIN'"

SOURCES += main.cpp\
    mainwindow.cpp \
    visualizationview.cpp \
    visualizationitemdata.cpp \
    visualization.cpp \
    texteditorprogrammers.cpp \
    texteditorlines.cpp \
    texteditorhighlighter.cpp \
    texteditor.cpp \
    settings.cpp \
    scriptthread.cpp \
    guivisualizationconnector.cpp \
    guimutex.cpp \
    guilogger.cpp \
    guifactory.cpp \
    guicontext.cpp \
    dockvisualization.cpp \
    dockvariables.cpp \
    dockscriptoutput.cpp \
    dockfiles.cpp \
    dockcallstack.cpp \
    dialogsettingsvisualization.cpp \
    dialogsettingseditor.cpp \
    dialogsettings.cpp \
    dialogscriptparameters.cpp \
    dialogreplaceconfirmation.cpp \
    dialogreplace.cpp \
    dialogincludedirs.cpp \
    dialogfind.cpp

HEADERS  += mainwindow.h \
    visualizationview.h \
    visualizationitemdata.h \
    visualization.h \
    texteditorprogrammers.h \
    texteditorlines.h \
    texteditorhighlighter.h \
    texteditor.h \
    settings.h \
    scriptthread.h \
    guivisualizationconnector.h \
    guimutex.h \
    guilogger.h \
    guifactory.h \
    guicontext.h \
    dockvisualization.h \
    dockvariables.h \
    dockscriptoutput.h \
    dockfiles.h \
    dockcallstack.h \
    dialogsettingsvisualization.h \
    dialogsettingseditor.h \
    dialogsettings.h \
    dialogscriptparameters.h \
    dialogreplaceconfirmation.h \
    dialogreplace.h \
    dialogincludedirs.h \
    dialogfind.h

FORMS += \
    dialogsettingsvisualization.ui \
    dialogsettingseditor.ui \
    dialogscriptparameters.ui \
    dialogreplaceconfirmation.ui \
    dialogreplace.ui \
    dialogincludedirs.ui \
    dialogfind.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    Makefile
