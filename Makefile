BUILD_DIR=build
BUILDTYPE?=Release

DEMO=$(BUILD_DIR)/libuv-demo

all: $(DEMO)

$(BUILD_DIR):
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILDTYPE)

$(DEMO): $(BUILD_DIR)
	cmake --build $(BUILD_DIR) -j $(JOBS)

install: $(DEMO)
	cmake --build $(BUILD_DIR) --target install