#!/bin/bash

error_exit() {
    echo "$1" >&2
    exit 1
}

install_on_linux() {
    if ! command -v doxygen &>/dev/null; then
        sudo apt-get update && \
        sudo apt-get install doxygen || \
        error_exit "Installation of doxygen failed"
    fi
}

install_on_darwin() {
    echo ""
}

platform=$(uname)

case $platform in
    Linux)
        install_on_linux
        ;;
    Darwin)
        install_on_darwin
        ;;
    *)
        error_exit "This script supports only Linux or Darwin"
esac

echo "doxygen installed successfully!"