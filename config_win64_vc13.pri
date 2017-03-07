
message( "Visual 2013 64 bits platform" )

QTDIR = $$[QT_INSTALL_PREFIX]

!include( build_path.pri ) {
	CONFIG( debug, debug|release ){
		BLD_PATH = $$(HOME)/software/build/Aimsun_8_2_debug
	}else{
		BLD_PATH = $$(HOME)/software/build/Aimsun_8_2_release
	}
	AIMSUN_SDK_DIR = $$(HOME)/software/sources/Flourish
}

message( $${BLD_PATH} )
message( $${AIMSUN_SDK_DIR} )

BIN_PATH = $${BLD_PATH}/bin
PLG_PATH = $${BLD_PATH}/bin/plugins
SLP_PATH = $${BLD_PATH}/lib

CONFIG += c++11
CONFIG += x86_64

QT += concurrent

INCLUDEPATH += $${AIMSUN_SDK_DIR}/include/core/ANG_DTA 
INCLUDEPATH += $${AIMSUN_SDK_DIR}/include/core/ANG_DTA/ADynamicAPI 
INCLUDEPATH += $${AIMSUN_SDK_DIR}/include/aimsun_extensions/V2XFramework

INCLUDEPATH += include/core/ANG_DTA
INCLUDEPATH += include/core/ANG_DTA/ADynamicAPI
INCLUDEPATH += include/aimsun_extensions/V2XFramework
#LIBS += -L$${AIMSUN_SDK_DIR}/lib  -lV2XFramework8
