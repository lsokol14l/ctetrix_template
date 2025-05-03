CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -std=c11
OFLAGS=-Wall -Wextra -Werror -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage

FRONTEND_TARGET_NAME = tetris_frontend_api

BACKEND_TARGET_NAME = tetris_backend_api
BACKEND_TEST_NAME = backend_unittest

COVERAGE_NAME = coverage.info

BACKEND_EXTERN_HEADER=$(BACKEND_TARGET_NAME).h
FRONTEND_EXTERN_HEADER=$(FRONTEND_TARGET_NAME).h

PROJECT_NAME=tetris