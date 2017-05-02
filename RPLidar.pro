QT += core
QT -= gui

TARGET = RPLidar

TEMPLATE = lib

INCLUDEPATH += include \ 
               3rdparty/rplidar_sdk/include

SOURCES += src/RPLidarPrivate.cpp \
           src/RPLidar.cpp

HEADERS += include/WestBot/RPLidar/private/RPLidarPrivate.hpp \
           include/WestBot/RPLidar/RPLidar.hpp

LIBS += -L../rplidar/3rdparty/rplidar_sdk/lib -lrplidar_sdk

DEFINES += WESTBOT_RPLIDARSHAREDLIB_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS
