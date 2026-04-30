BUILD_DIR ?= build
TARGETS ?= seq;mt_pth;seq_checks

GENERATOR ?= "Unix Makefiles"

.PHONY: all build clean

all: build

build:
	git submodule update --init --recursive
	cmake -S . -B $(BUILD_DIR) -G ${GENERATOR} -DTARGETS="$(TARGETS)"
	+cmake --build $(BUILD_DIR_RELEASE)

clean:
	$(RM) -r $(BUILD_DIR)
