#!/bin/bash

error_exit() {
    echo "$1" >&2
    exit 1
}

uninstall_on_linux() {
    if pkg-config --libs check &>/dev/null; then
         sudo apt-get remove check || error_exit "check.h uninstall failure"
    fi
}

uninstall_on_darwin() {
    if pkg-config --libs check &>/dev/null; then
        brew uninstall check || error_exit "check.h uninstall failure"
    fi
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
        error_exit "This script support only Linux or darwin"
esac

echo " libcheck.h uninstall successfully!"