TARGET_EXEC ?= main

BUILD_DIR ?= ./build
SRC_DIR ?= ./src
INC_DIR ?= ./inc
LDFLAGS ?= -lglut -lGLU  -lGL

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

FLAGS ?= -I$(INC_DIR) -Wall -Wextra -g 

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	g++ $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	g++ $(FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)