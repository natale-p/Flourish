
message( "Visual 2013 64 bits platform" )

QTDIR = $$[QT_INSTALL_PREFIX]

message( $${BLD_PATH} )
message( $${AIMSUN_SDK_DIR} )

BIN_PATH = $${BLD_PATH}/bin
PLG_PATH = $${BLD_PATH}/bin/plugins
SLP_PATH = $${BLD_PATH}/lib

CONFIG += c++11
CONFIG += x86_64

QT += concurrent
