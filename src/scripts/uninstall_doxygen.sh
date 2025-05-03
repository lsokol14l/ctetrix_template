#!/bin/bash

error_exit() {
    echo "$1" >&2
    exit 1
}

uninstall_on_linux() {
    if ! command -v doxygen &>/dev/null; then
        sudo apt-get update && \
        sudo apt-get uninstall doxygen || \
        error_exit "uninstallation of doxygen failed"
    fi
}

uninstall_on_darwin() {
    echo ""
}

platform=$(uname)

case $platform in
    Linux)
        uninstall_on_linux
        ;;
    Darwin)
        uninstall_on_darwin
        ;;
    *)
        error_exit "This script supports only Linux or Darwin"
esac

echo "doxygen uninstalled successfully!"