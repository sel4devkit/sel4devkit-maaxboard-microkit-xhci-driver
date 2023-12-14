#!/bin/bash
export MICROKIT_BOARD="maaxboard"
export MICROKIT_CONFIG="debug"
export MICROKIT_TOOL="python -m microkit"

export MICROKIT_DIR="$HOME/mk-manifest/microkit" #! change this to microkit directory
export MICROKIT_SDK="$MICROKIT_DIR/release/microkit-sdk-1.2.6"
export BOARD_DIR="$MICROKIT_SDK/board/$MICROKIT_BOARD/$MICROKIT_CONFIG"
export BUILD_DIR="$MICROKIT_DIR/tmp_build"

export PYTHONPATH="$MICROKIT_DIR/tool"
export PATH="$MICROKIT_DIR/../compiler/bin:$PATH"

export SEL4_XHCI_PATH=$MICROKIT_DIR/example/maaxboard/xhci_stub
export NETBSD_DIR="$SEL4_XHCI_PATH/netbsd/src"

make -C $SEL4_XHCI_PATH
# if clean
# make clean

# specific to capgemini implementation
echo 
TFTP_LOCATION="/var/lib/tftpboot/loader-josh.img"
sudo cp $BUILD_DIR/loader.img $TFTP_LOCATION
if [ $? -gt 0 ]; then
    echo "Error(s) detected, file not copied"
else
    echo Copied image file to "$TFTP_LOCATION".
fi