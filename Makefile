BUILD_DIR ?= build
THREADS   ?= 4
TARGETS   ?= seq;mt_pth

.PHONY: all build clean

all: build

build:
	git submodule init
	git submodule update
	cd $(BUILD_DIR) && cmake -DTARGETS="$(TARGETS)" .. && make -j$(THREADS)

clean:
	$(RM) -r $(BUILD_DIR)
