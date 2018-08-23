CC = gcc
CFLAGS = -fpic -Wall -Wextra -O2
LDFLAGS = -shared

SRC = quaternions.c
SOURCE_DIR = src
BUILD_DIR = build
TARGET_LIB = quaternions.so

.PHONY: all
all: ${TARGET_LIB}

${TARGET_LIB}: ${SOURCE_DIR}/${SRC}
	mkdir -p ${BUILD_DIR}
	$(CC) ${LDFLAGS} -o ${BUILD_DIR}/$@ $^

.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}