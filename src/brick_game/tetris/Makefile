include ../../makefiles/common.mk

SOURCE_DIR = .
TEST_DIR = ./tests
BUILD_DIR = ../../../build
SCRIPTS_DIR = ../../scripts

COMMON_INCLUDE_PATH=../../includes
INCLUDE_FLAGS = -I$(SOURCE_DIR) -I$(COMMON_INCLUDE_PATH)

SOURCES = $(shell find $(SOURCE_DIR) -type f -name "*.c" -not -path "$(TEST_DIR)/*")
TEST_SOURCES = $(shell find $(TEST_DIR) -type f -name "*.c")


OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SOURCES))


all: $(BACKEND_TARGET_NAME)

$(BACKEND_TARGET_NAME):  $(OBJECTS)
	mkdir -p $(BUILD_DIR)/lib
	ar -rs $(BUILD_DIR)/lib/lib$@.a $(OBJECTS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(shell pkg-config --cflags check) $< -o $@

test: unittest
	./$(BUILD_DIR)/$(BACKEND_TEST_NAME)

unittest: $(BACKEND_TARGET_NAME) $(TEST_OBJECTS)
	$(CC) $(OFLAGS) $(TEST_OBJECTS) -L$(BUILD_DIR)/lib -l$(BACKEND_TARGET_NAME) $(shell pkg-config --libs check) -o ./$(BUILD_DIR)/$(BACKEND_TEST_NAME)

leaktest: unittest
	@bash $(SCRIPTS_DIR)/leak_test.sh

gcov_report: $(TEST_OBJECTS)
	$(CC) $(OFLAGS) $(GCOVFLAGS) $(INCLUDE_FLAGS) $(TEST_OBJECTS) $(SOURCES) $(shell pkg-config --libs check) -o ./$(BACKEND_TEST_NAME)
	./$(BACKEND_TEST_NAME)
	lcov -t "gcov_report" -o $(COVERAGE_NAME) -c -d $(SOURCE_DIR) 
	genhtml -q -s -o ./report $(COVERAGE_NAME)

clean:
	@rm -rf $(OBJECTS)
	@rm -f $(BUILD_DIR)/lib/lib$(BACKEND_TARGET_NAME).a

	@rm -rf $(TEST_OBJECTS)
	@rm -rf $(BUILD_DIR)/$(BACKEND_TEST_NAME)

	@rm -rf $(SOURCE_DIR)/$(BACKEND_TEST_NAME)
	@rm -rf $(SOURCE_DIR)/report
	@rm -rf $(SOURCE_DIR)/$(COVERAGE_NAME)

	@find . -name '*.gcov' -delete
	@find . -name '*.gcda' -delete
	@find . -name '*.gcno' -delete
	

rebuild: clean all

include ../../makefiles/linters.mk