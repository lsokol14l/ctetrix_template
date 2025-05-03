#!/bin/bash

error_exit() {
    echo "$1" >&2
    exit 1
}

uninstall_on_linux() {
    if command -v lcov &>/dev/null; then
        sudo apt-get remove lcov || \
        error_exit "uninstallation of lcov failed"
    fi
}

uninstall_on_darwin() {
    if command -v lcov &>/dev/null; then
        brew uninstall lcov || \
        error_exit "uninstallation of gcov, lcov failed"
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
        error_exit "This script supports only Linux or Darwin"
esac

echo "gcov, lcov, and genhtml uninstalled successfully!"