#-------------------------------------------------
#
# Project created by QtCreator 2015-07-11T19:08:41
#
#-------------------------------------------------

QT       += core gui xml
CONFIG   += qt c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projectizer
TEMPLATE = app


SOURCES += src/main.cpp\
    src/windows/main_window/CMainWindow.cpp \
    src/parser/CProjectXmlFileReader.cpp \
    src/parser/CProjectTypeXmlFileReader.cpp \
    src/parser/AXmlFileReader.cpp \
    src/parser/COption.cpp \
    src/saved_projects/model/CProjectModel.cpp \
    src/file_finder/CXMLFileFinder.cpp \
    src/CConstants.cpp \
    src/saved_projects/view/CSavedProjectsTableView.cpp \
    src/windows/configure_dialog/CConfigureProjectDialog.cpp \
    src/parser/CProjectXmlFileWriter.cpp \
    src/application/CApplication.cpp

HEADERS  += \
    src/windows/main_window/CMainWindow.hpp \
    src/parser/CProjectXmlFileReader.hpp \
    src/parser/CProjectTypeXmlFileReader.hpp \
    src/parser/AXmlFileReader.hpp \
    src/parser/COption.hpp \
    src/saved_projects/model/CProjectModel.hpp \
    src/file_finder/CXMLFileFinder.hpp \
    src/CConstants.hpp \
    src/saved_projects/view/CSavedProjectsTableView.hpp \
    src/windows/configure_dialog/CConfigureProjectDialog.hpp \
    src/parser/CProjectXmlFileWriter.hpp \
    src/application/CApplication.hpp

FORMS    += ui/MainWindow.ui \
    ui/ConfigureProjectDialog.ui

OTHER_FILES += \
    project.xml \
    project_type.xml
