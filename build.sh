#!/bin/bash
export MICROKIT_BOARD="maaxboard"
export MICROKIT_CONFIG="debug"
export MICROKIT_TOOL="python -m microkit"

export MICROKIT_DIR="$HOME/xhci-manifest/microkit" #! change this to microkit directory
export MICROKIT_SDK="$MICROKIT_DIR/out/microkit-sdk-1.2.6"
export BOARD_DIR="$MICROKIT_SDK/board/$MICROKIT_BOARD/$MICROKIT_CONFIG"

export PYTHONPATH="$MICROKIT_DIR/tool"
export PATH="$MICROKIT_DIR/../compiler/bin:$PATH"

export SEL4_XHCI_PATH=$( dirname -- "$( readlink -f -- "$0"; )"; )
export BUILD_DIR=$SEL4_XHCI_PATH/xhci_build
export NETBSD_DIR="$SEL4_XHCI_PATH/netbsd/src"

mkdir -p "$BUILD_DIR"

examples=( "shell" "empty-client" "FatFs")

print_examples() {
    echo "EXAMPLES:"
    for e in "${examples[@]}"; do
        echo "  $e"
    done
}

print_usage() {
    echo "usage: ./build.sh [OPTION] -e [EXAMPLE]"
    echo
    echo "OPTIONS:"
    echo "  -r rebuild"
    echo "      rebuild all files (use when modifying headers or en/disabling debug)"
    echo "  -c clean"
    echo "      remove build files"
    echo "  -d debug"
    echo "      enable debugging output"
    echo "  -p compile"
    echo "      create compiler include paths (for clangd)"
    echo
    print_examples
    exit 1
}

while getopts 'e:rcpd' flag; do
  case "${flag}" in
    e) export EXAMPLE="${OPTARG}" ;;
    r) rebuild="true" ;;
    c) clean="true" ;;
    d) export SEL4_USB_DEBUG="true" ;;
    p) compiler="true";;
    *) print_usage ;;
  esac
done

if [ -z "$EXAMPLE" ]; then
    print_usage
fi

opt=${@:$OPTIND:1}

if [[ ! " ${examples[*]} " =~ [[:space:]]${EXAMPLE}[[:space:]] ]]; then
    # whatever you want to do when array doesn't contain value
    echo "error: example '$EXAMPLE' not found!"
    echo
    print_examples
    exit 1
fi

if [ "$clean" = "true" ] ; then
    make -C "$SEL4_XHCI_PATH" clean
elif [ "$rebuild" = "true" ]; then
    make -C "$SEL4_XHCI_PATH" clean
    make -C "$SEL4_XHCI_PATH"
elif [ "$compiler" = "true" ]; then
    make -C "$SEL4_XHCI_PATH" clean
    make -C "$SEL4_XHCI_PATH" --always-make --dry-run \
    | grep -wE 'gcc|g\+\+' \
    | grep -w '\-c' \
    | jq -nR '[inputs|{directory:".", command:., file: match(" [^ ]+$").string[1:]}]' \
    > compile_commands.json
else
    make -C "$SEL4_XHCI_PATH"
fi

# specific to capgemini implementation
echo 
TFTP_LOCATION="/var/lib/tftpboot/loader-josh.img"
sudo cp $BUILD_DIR/loader.img $TFTP_LOCATION
if [ $? -gt 0 ]; then
    echo "Error(s) detected, file not copied"
else
    echo Copied image file to "$TFTP_LOCATION".
fi
