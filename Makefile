BIN_FILE = easypg

SRC_FILES += main.c
SRC_FILES += random.c
SRC_FILES += memory.c
SRC_FILES += generator.c

CC = gcc

INSTALL_DIR = /usr/local/bin

CFLAGS += -Iinclude
CFLAGS += -Wall -Wextra -Wuninitialized
build: CFLAGS += -g0 -s -O3 -DNDEBUG
debug: CFLAGS += -g3 -ggdb3 -O0 -DDEBUG

LDFLAGS += -lssl -lcrypto

ifeq ($(CC), gcc)
endif

ifeq ($(CC), clang)
endif

ifeq ($(CC), x86_64-w64-mingw32-gcc)
	CFLAGS += -D__USE_MINGW_ANSI_STDIO
	LDFLAGS += -static -lws2_32
endif

ifeq ($(CC), i686-w64-mingw32-gcc)
	CFLAGS += -D__USE_MINGW_ANSI_STDIO
	LDFLAGS += -static -lws2_32
endif


OBJ_FILES := $(patsubst %.c,obj/%.o,$(SRC_FILES))
QUIET_CC = @echo '   ' CC $(notdir $@);

VPATH := src/

#.ONESHELL:
.PHONY: build debug test docs

all: build

build: mkdirs _build

debug: mkdirs _debug

_build: $(OBJ_FILES)
	$(CC) $^ -o bin/$(BIN_FILE) $(LDFLAGS)

_debug: $(OBJ_FILES)
	$(CC) $^ -o bin/$(BIN_FILE) $(LDFLAGS)

test:
	$(warning Tests now is not available!)

docs:
	doxygen docs/Doxyfile

obj/%.o: %.c
	$(QUIET_CC) $(CC) -c $< -o $@ $(CFLAGS)

install: mkdirs build
	install bin/$(BIN_FILE) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(BIN_FILE)

clean:
	rm -f obj/*
	rm -f bin/*

mkdirs: 
	@if [ ! -d bin ]; then \
		mkdir bin; \
	fi

	@if [ ! -d obj ]; then \
		mkdir obj; \
	fi
