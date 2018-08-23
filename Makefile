CC := gcc
C_FLAGS := -fpic -Wall -Wextra -O2
LINKFLAGS := -shared

.PHONY: $(TARGET)
.PHONY: clean

SRC_PATH := ./src/
BUILD_PATH := ./build/
INCLUDE_PATH := ./include

TARGET := quaternions.so

OBJS := quaternions.o
OBJ := $(patsubst %,$(BUILD_PATH)%,$(OBJS))

$(BUILD_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(BUILD_PATH)
	@$(CC) $(C_FLAGS) -o $@ -c $< -I $(INCLUDE_PATH)

$(TARGET): $(OBJ)
	@$(CC) -o $(BUILD_PATH)$@ $^ $(LINKFLAGS)

clean:
	@rm -rf $(BUILD_PATH)