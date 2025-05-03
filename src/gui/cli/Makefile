include ../../makefiles/common.mk

SOURCE_DIR = .
BUILD_DIR = ../../../build
SCRIPTS_DIR = ../../scripts


COMMON_INCLUDE_PATH=../../includes
INCLUDE_FLAGS = -I$(SOURCE_DIR) -I$(COMMON_INCLUDE_PATH)

SOURCES = $(shell find $(SOURCE_DIR) -type f -name "*.c" -not -path "$(TEST_DIR)/*")

OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(FRONTEND_TARGET_NAME)

$(FRONTEND_TARGET_NAME):  $(OBJECTS)
	mkdir -p $(BUILD_DIR)/lib
	ar -rs $(BUILD_DIR)/lib/lib$@.a $(OBJECTS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(shell pkg-config --cflags ncurses) $(INCLUDE_FLAGS) $< -o $@

clean:
	@rm -rf $(OBJECTS)
	rm -f $(BUILD_DIR)/lib/lib$(FRONTEND_TARGET_NAME).a
	

rebuild: clean all

include ../../makefiles/linters.mk