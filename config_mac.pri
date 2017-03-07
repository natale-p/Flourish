
message( "Mac OS X 64 bits platform" )

QTDIR = $$[QT_INSTALL_PREFIX]

!include( build_path.pri ) {
	CONFIG( debug, debug|release ){
		BLD_PATH = $$(HOME)/software/build/Aimsun_8_2_debug
	}else{
		BLD_PATH = $$(HOME)/software/build/Aimsun_8_2_release
	}
	AIMSUN_SDK_DIR = $$(HOME)/software/sources/Aimsun_8_2
}

message( $${BLD_PATH} )
message( $${AIMSUN_SDK_DIR} )

BIN_PATH = $${BLD_PATH}/bin
SLP_PATH = $${BLD_PATH}/lib

MIN_SDK = -mmacosx-version-min=10.9
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

CONFIG += c++11
QMAKE_MAC_SDK = macosx10.12
QMAKE_CXXFLAGS	+=
QMAKE_LFLAGS	+= -rpath @executable_path/../Frameworks -rpath @executable_path/../PlugIns
CONFIG-=depend_includepath

QMAKE_CFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON -= -Wall

QMAKE_CFLAGS_DEBUG   += -Wall -Wno-overloaded-virtual -Wno-reorder -Wno-dynamic-class-memaccess -Werror=return-type -Wvla
QMAKE_CXXFLAGS_DEBUG += -Wall -Wno-overloaded-virtual -Wno-reorder -Wno-dynamic-class-memaccess -Werror=return-type -Wvla

QMAKE_CFLAGS_DEBUG		+= $$QMAKE_CFLAGS_DWARF2
QMAKE_CXXFLAGS_DEBUG	+= $$QMAKE_CFLAGS_DWARF2

QMAKE_CFLAGS	+= $$MIN_SDK
QMAKE_CXXFLAGS	+= $$MIN_SDK
QMAKE_LFLAGS	+= $$MIN_SDK
QMAKE_OBJECTIVE_CFLAGS += $$MIN_SDK

CONFIG += x86_64

QMAKE_LFLAGS_SHLIB += -fPIC

INCLUDEPATH += $${AIMSUN_SDK_DIR}/include/core/ANG_DTA 
INCLUDEPATH += $${AIMSUN_SDK_DIR}/include/core/ANG_DTA/ADynamicAPI 
INCLUDEPATH += $${AIMSUN_SDK_DIR}/include/aimsun_extensions/V2XFramework

DEFINES += _USE_GDAL
GDAL_LIBS = -F/Library/Frameworks -framework GDAL
INCLUDEPATH += /Library/Frameworks/GDAL.framework/Headers/

SPATIAL_INCL = $${QTDIR}/extras/spatialindex/include/spatialindex
SPATIAL_LIBS = -L$${QTDIR}/extras/spatialindex/lib
SPATIAL_LIBS += -lspatialindex

BOOST_INCL = $$QTDIR/extras/boost/include
BOOST_LIBS = -L$$QTDIR/extras/boost/lib
