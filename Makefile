SHELL := bash
ENV := CC=/usr/bin/clang CXX=/usr/bin/clang++
FORMAT := clang-format

INCLUDE_DIR := include
INCLUDE_FILES := $(INCLUDE_DIR)/*.h
SRC_DIR := src
SRC_FILES := $(SRC_DIR)/*.cpp
TEST_DIR := test
TEST_FILES := $(TEST_DIR)/*.cpp
BUILD_DIR := build

.DEFAULT_GOAL := build

build: $(INCLUDE_FILES) $(SRC_FILES) $(TEST_FILES)
	$(ENV) cmake -B $(BUILD_DIR) -G Ninja
	@cd $(BUILD_DIR) && ninja -j 8

rbtree: build
	cd $(BUILD_DIR) && $(SRC_DIR)/rbtree

# default test target
TEST_NAME ?= vector

test: build
	@$(BUILD_DIR)/$(TEST_DIR)/$(TEST_NAME)_test

test-all: build
	for f in $(BUILD_DIR)/$(TEST_DIR)/*_test; do \
		printf "\033[32m`tput bold`Running `basename $$f`...`tput sgr0`\033[0m\n"; \
		$(BUILD_DIR)/$(TEST_DIR)/`basename $$f`; \
	done

clean:
	rm -rf build

format:
	$(FORMAT) -i $(INCLUDE_FILES) $(SRC_FILES) $(TEST_FILES)

commit ?= test

push:
	@git add .
	@git commit -m "$(commit)"
	@git push
	@sync #sync all files in os
