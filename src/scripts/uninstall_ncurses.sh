#!/bin/bash

error_exit() {
    echo "$1" >&2
    exit 1
}

uninstall_on_linux() {
    if pkg-config --libs ncurses &>/dev/null; then
        sudo apt-get remove libncurses5-dev libncursesw5-dev || error_exit "ncurses.h uninstall failure"
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

echo "ncurses uninstalled successfully!"