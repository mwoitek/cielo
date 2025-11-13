CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Werror -Wpedantic -O2 -fPIC
LDFLAGS = -lm
LUA_INC = $(shell pkg-config --cflags lua5.1)

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
	$(CC) -shared $^ -o $@ $(LDFLAGS)

clean:
	$(RM) -r $(BUILD_DIR)

# TODO: this is for quick testing, and eventually should be removed
test: $(BUILD_DIR)/cielo_test

$(BUILD_DIR)/cielo_test: $(filter-out %_lua.c, $(wildcard src/*.c)) | $(BUILD_DIR)
	$(CC) -std=c99 -g -O0 -o $@ $^ $(LDFLAGS) && valgrind -q $@

.PHONY: all clean test
