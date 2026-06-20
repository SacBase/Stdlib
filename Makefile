BUILD_DIR ?= build
TARGETS ?= "seq;mt_pth;seq_checks"

GENERATOR ?= "Unix Makefiles"

.PHONY: all build clean

all: build

build:
	cmake -S . -B $(BUILD_DIR) -G $(GENERATOR) -DTARGETS=$(TARGETS)
	+cmake --build $(BUILD_DIR)

clean:
	$(RM) -r $(BUILD_DIR)
