SCHEME = gpucompute
CONFIG = Release
DEST_DIR = /usr/local/lib

DERIVED_DATA_DIR = build
PRODUCTS_DIR = $(DERIVED_DATA_DIR)/Build/Products/$(CONFIG)

METALLIB_SRC = $(PRODUCTS_DIR)/default.metallib
METALLIB_DST = $(DEST_DIR)/gpucompute.metallib

DYLIB_SRC = $(PRODUCTS_DIR)/libgpucompute.dylib
DYLIB_DST = $(DEST_DIR)/libgpucompute.dylib

ARCH = arm64
PLATFORM = macOS
DESTINATION = platform=$(PLATFORM),arch=$(ARCH)

.PHONY: all build install clean

# default target: build
all: build

# build using Xcode
build:
	xcodebuild -scheme $(SCHEME) -configuration $(CONFIG) -derivedDataPath $(DERIVED_DATA_DIR) -destination $(DESTINATION)

# install
install: build
	@echo "Installing the Metal library in $(METALLIB_DST) ..."
	sudo install -m 644 $(METALLIB_SRC) $(METALLIB_DST)
	sudo strip -x $(METALLIB_DST)

	@echo "Installing the dynamic library in $(DYLIB_DST) ..."
	sudo install -m 755 $(DYLIB_SRC) $(DYLIB_DST)

	@echo "Installation completed."

clean:
	xcodebuild -scheme $(SCHEME) -configuration $(CONFIG) -derivedDataPath $(DERIVED_DATA_DIR) -destination $(DESTINATION) clean
	rm -rf $(DERIVED_DATA_DIR)
