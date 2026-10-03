# Program Variables
PROGNAME := PolyCepharithm
SOURCE_DIR := ./source
BUILD_DIR  := ./build
VENDOR_DIR := ./vendor

# Compilation Variables
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -g -MMD -MP
CPPFLAGS := -Isource -Ivendor
LDFLAGS  :=

TARGET := $(BUILD_DIR)/$(PROGNAME)

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS    := $(OBJECTS:.o=.d)

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean
	$(MAKE) all

-include $(DEPS)