CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Werror -Wpedantic -O2 -fPIC
LUA_INC = -I/usr/include/lua5.1

BUILD_DIR = build
LUA_MOD = $(BUILD_DIR)/cielo.so

all: $(LUA_MOD)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/cielo.o: $(addprefix src/,cielo.c cielo.h) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/cielo_lua.o: src/cielo_lua.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LUA_INC) -c $< -o $@

$(LUA_MOD): $(addprefix $(BUILD_DIR)/,cielo.o cielo_lua.o)
	$(CC) -shared $^ -o $@ -lm

clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: all clean
