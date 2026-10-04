# Program Variables
PROGNAME := PolyCepharithm
SOURCE_DIR := ./source
BUILD_DIR  := ./build
VENDOR_DIR := ./vendor

TARGET := $(BUILD_DIR)/$(PROGNAME)

# Compilation Variables
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -g -MMD -MP
CPPFLAGS := -I$(SOURCE_DIR) -I$(VENDOR_DIR)/GLAD/include -I$(VENDOR_DIR)/GLFW/include
LDLIBS   := 
LDFLAGS  := 

UNAME_S  := $(shell uname -s)
ifeq ($(UNAME_S), Linux) # Link Linux GLFW Libraries
	LDLIBS  += -L$(VENDOR_DIR)/GLFW/libraries/linux -L$(VENDOR_DIR)/GLAD/libraries/linux
	LDFLAGS += -lglad -lglfw3 -lGL -lX11 -lwayland-client -lxkbcommon -lxcb
endif

ifneq ($(findstring MINGW64, $(UNAME_S)), ) # Link Windows GLFW Libraries
	LDLIBS  += -L$(VENDOR_DIR)/GLFW/libraries/windows -L$(VENDOR_DIR)/GLAD/libraries/windows
	LDFLAGS += -lglad -lglfw3dll

	TARGET  := $(BUILD_DIR)/$(PROGNAME).exe 
endif

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS    := $(OBJECTS:.o=.d)

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDLIBS) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(shell mkdir -p $(BUILD_DIR))
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean
	$(MAKE) all

-include $(DEPS)