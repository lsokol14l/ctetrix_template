include ./makefiles/common.mk

INCLUDE_PATH=./includes

BACKEND_DIR=./brick_game/tetris

FRONTEND_DIR=./gui/cli

SCRIPTS_DIR = ./scripts
BUILD_DIR=../build
TEMP_DIST_DIR=../dist/temp
SOURCE_DIR=.

all: copy_includes backend frontend
	gcc -I./includes main.c -o $(BUILD_DIR)/$(PROJECT_NAME) -L./../build/lib -ltetris_frontend_api -ltetris_backend_api $(shell pkg-config --libs ncurses) -lm

backend:
	$(MAKE) -C $(BACKEND_DIR) all

frontend:
	$(MAKE) -C $(FRONTEND_DIR) all

test:
	@$(MAKE) -C $(BACKEND_DIR) unittest
	@$(MAKE) -C $(BACKEND_DIR) test
	
copy_includes:
	cp $(BACKEND_DIR)/$(BACKEND_EXTERN_HEADER) $(INCLUDE_PATH) 
	cp $(FRONTEND_DIR)/$(FRONTEND_EXTERN_HEADER) $(INCLUDE_PATH) 

clean:
	$(MAKE) -C $(BACKEND_DIR) clean
	rm -rf $(INCLUDE_PATH)/$(BACKEND_EXTERN_HEADER)
	$(MAKE) -C $(FRONTEND_DIR) clean
	rm -rf $(INCLUDE_PATH)/$(FRONTEND_EXTERN_HEADER)
	rm -rf $(BUILD_DIR)
	rm -rf $(PROJECT_NAME)
	rm -rf ../dist
	rm -rf .tar.swp
	rm -rf ../dvi

install: install_dependence install_coverage_dependence

install_dependence:
	@bash $(SCRIPTS_DIR)/install_pkg_config.sh
	@bash $(SCRIPTS_DIR)/install_check.sh
	@bash $(SCRIPTS_DIR)/install_ncurses.sh
	@bash $(SCRIPTS_DIR)/install_doxygen.sh

install_coverage_dependence:
	@bash $(SCRIPTS_DIR)/install_gcov.sh


uninstall:  uninstall_coverage_dependence uninstall_dependence

uninstall_dependence:
	@bash $(SCRIPTS_DIR)/uninstall_check.sh
	@bash $(SCRIPTS_DIR)/uninstall_ncurses.sh
	@bash $(SCRIPTS_DIR)/uninstall_doxygen.sh

uninstall_coverage_dependence:
	@bash $(SCRIPTS_DIR)/uninstall_gcov.sh

gcov_report: clean
	@$(MAKE) -C $(BACKEND_DIR) gcov_report
	
	mkdir -p $(BUILD_DIR)/reports/build
	mv $(BACKEND_DIR)/report $(BUILD_DIR)/reports/report
	find $(BACKEND_DIR) -type f -name "*.gcov" -exec mv {} $(BUILD_DIR)/reports/build/ \;
	find $(BACKEND_DIR) -type f -name "*.gcda" -exec mv {} $(BUILD_DIR)/reports/build/ \;
	find $(BACKEND_DIR) -type f -name "*.gcno" -exec mv {} $(BUILD_DIR)/reports/build/ \;
	mv $(BACKEND_DIR)/coverage.info $(BUILD_DIR)/reports/build/backend_coverage.info
	mv $(BACKEND_DIR)/backend_unittest $(BUILD_DIR)/reports/build/backend_unittest


dist:
	mkdir -p $(TEMP_DIST_DIR)
	cp -r . $(TEMP_DIST_DIR)/
	tar -czvf ../dist/s21_tetris.tar.gz -C $(TEMP_DIST_DIR) .
	rm -rf $(TEMP_DIST_DIR)

dvi:
	doxygen
	
include ./makefiles/linters.mk