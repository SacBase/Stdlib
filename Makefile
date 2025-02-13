BUILD_DIR ?= build
THREADS   ?= 4
TARGETS   ?= seq;mt_pth;seq_checks

.PHONY: all build clean

all: build

build:
	git submodule update --init --recursive
	mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && \
		cmake -DTARGETS="$(TARGETS)" .. && make -j$(THREADS)

clean:
	$(RM) -r $(BUILD_DIR)
