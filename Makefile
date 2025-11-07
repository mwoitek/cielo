CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Werror -Wpedantic -O2 -fPIC
LUA_INC = -I/usr/include/lua5.1

BUILD_DIR = build
LUA_MOD = $(BUILD_DIR)/cielo.so

all: $(LUA_MOD)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/cielo_lua.o: src/cielo_lua.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LUA_INC) -c $< -o $@

$(BUILD_DIR)/%.o: src/%.c src/%.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LUA_MOD): $(BUILD_DIR)/*.o
	$(CC) -shared $^ -o $@ -lm

clean:
	$(RM) -r $(BUILD_DIR)

# TODO: this is for quick testing, and eventually should be removed
test:
	$(CC) -std=c99 -g -O0 -o $(BUILD_DIR)/cielo_test $(addprefix src/,cielo_test.c cielo.c) -lm

.PHONY: all clean test
