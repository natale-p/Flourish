
# How to add a dependency
#
# 0) Decide if the dependency should be compiled or taken from system
# 1) Check the existence of the library/include file
# 2) Define the FOO_INCL and FOO_LIBS variables
# 3) If these variables are empty, print an error
# 4) Update the .pro file to use these variables
# 5) Update the copy_lib script after the build process

message( "LINUX 64 bits platform" )

QTDIR = $$[QT_INSTALL_PREFIX]

CONFIG( debug, debug|release ){
	DEFINES += _DEBUG
}else{
	DEFINES += NDEBUG
}

QMAKE_CFLAGS_DEBUG   += -g3 -O0 -Wall -Wextra -Wno-deprecated
QMAKE_CXXFLAGS_DEBUG += -g3 -O0 -Wall -Wextra -Wno-deprecated

QMAKE_LFLAGS_SHLIB += -fPIC '-Wl,-rpath,\'\$$ORIGIN:\$$ORIGIN/../../plugins:\$$ORIGIN/../..\''
QMAKE_LFLAGS += -Wl,--no-undefined '-Wl,-rpath,\'\$$ORIGIN:\$$ORIGIN/../../plugins:\$$ORIGIN/../..\''

CONFIG += x86_64

QMAKE_LFLAGS_SHLIB += -fPIC

BIN_PATH = $${BLD_PATH}/bin
PLG_PATH = $${BIN_PATH}/plugins
SLP_PATH = $${BLD_PATH}/lib

