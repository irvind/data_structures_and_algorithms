# inspired by:
# https://scaron.info/blog/makefile-for-a-simple-c-project.html
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
# https://makefiletutorial.com/

BUILD_DIR ?= ./build
SRC_DIR ?= ./src

TARGET = ds
CFLAGS = -Wall -O2

MKDIR_P ?= mkdir -p

$(TARGET): $(BUILD_DIR)/hash_table.o
	gcc $(BUILD_DIR)/hash_table.o $(CFLAGS) -o $(TARGET)

$(BUILD_DIR)/hash_table.o: $(SRC_DIR)/hash_table.c
	$(MKDIR_P) $(BUILD_DIR)
	gcc -c $(SRC_DIR)/hash_table.c $(CFLAGS) -o $(BUILD_DIR)/hash_table.o

all: $(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

