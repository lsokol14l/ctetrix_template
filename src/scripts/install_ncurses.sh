#!/bin/bash

error_exit() {
    echo "$1" >&2
    exit 1
}

install_on_linux() {
    if ! pkg-config --libs ncurses &>/dev/null; then
        sudo apt-get update && sudo apt-get install libncurses5-dev libncursesw5-dev || error_exit "ncurses.h install failure"
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

echo "ncurses installed successfully!"