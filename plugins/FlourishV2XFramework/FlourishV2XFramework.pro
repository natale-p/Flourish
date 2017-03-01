SUB_PROJECT_NAME = FlourishV2XFramework
BASE_DIR = ../../../..
include (../../config.incl)

SOURCES += \
	FlourishConnectedAgent.cpp \
	FlourishV2XFramework.cpp \
	FlourishV2XBroker.cpp \
	FlourishVehicleRulesEngine.cpp \
	FlourishCAMMessage.cpp

HEADERS += \
        FlourishV2XFrameworkUtil.h \
	FlourishConnectedAgent.h \
	FlourishV2XFramework.h \
	FlourishV2XBroker.h \
	FlourishVehicleRulesEngine.h \
	FlourishCAMMessage.h

macx {

        TARGET = $${BIN_PATH}/Aimsun.app/Contents/PlugIns/FlourishV2XFramework
	QMAKE_LFLAGS_SONAME  = -Wl,-install_name,@rpath/
}else{
	linux {
                TARGET = $${BIN_PATH}/plugins/FlourishV2XFramework
	}else{
                TARGET = $${BIN_PATH}/plugins/FlourishV2XFramework
	}
}

#-------------------------------------------------------------------------------------

TEMPLATE = lib
VERSION = 8.2.0

CONFIG += dll qt thread exceptions rtti

win32 {
    DEFINES += _FlourishV2XFrameworkEXTDLL_DEF
}

QT += sql xml
greaterThan(QT_MAJOR_VERSION, 4) {
	QT += widgets
}

INCLUDEPATH += $$PTH_INCL


DEPENDPATH += $$INCLUDEPATH

#LIBS += $$STL_LIBS
LIBS += $$PTH_LIBS -L$${SLP_PATH}

win32 {
    message( $${BIN_PATH} )
    message($${PLG_PATH})
    LIBS += -L$${BIN_PATH} -lV2XFramework8
    LIBS += -L$${PLG_PATH} -ldtakernel8

} macx {
	LIBS += $$QWT_LIBS $$GDAL_LIBS $$QSCINDILLA_LIBS
	#LIBS += -L$${BIN_PATH}/AIMSUN.app/Contents/Frameworks -langkernel
	#LIBS += -L$${BIN_PATH}/AIMSUN.app/Contents/PlugIns -laimsunmicroplugin -ldtakernel -la2kernel -lacontrol
    LIBS += -L$${BIN_PATH}/AIMSUN.app/Contents/PlugIns -ldtakernel
    LIBS += -L$${BIN_PATH}/AIMSUN.app/Contents/Frameworks -lV2XFramework

} linux {
	LIBS += $$QWT_LIBS $$GDAL_LIBS $$QSCINDILLA_LIBS
#	LIBS += -L$${BIN_PATH} -langkernel
#	LIBS += -L$${BIN_PATH}/plugins -la2kernel -laimsunmicroplugin -ldtakernel -lacontrol
	LIBS += -L$${PLG_PATH} -ldtakernel
    LIBS += -L$${BIN_PATH} -lV2XFramework

	# asumimos que en linux usamos gcc >= 4.0
	# Las STL no se llevan bien con la visibilidad
	# LIBS += -z defs
	# QMAKE_CXXFLAGS_SHLIB += -fvisibility=hidden -fvisibility-inlines-hidden
}

#-------------------------------------------------------------------------------------
