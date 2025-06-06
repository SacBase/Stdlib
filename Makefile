BUILD_DIR ?= build
TARGETS   ?= seq;mt_pth;seq_checks

.PHONY: all build clean

all: build

build:
	git submodule update --init --recursive
	mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && \
		cmake -DTARGETS="$(TARGETS)" .. && $(MAKE)

clean:
	$(RM) -r $(BUILD_DIR)
