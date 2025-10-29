#include "cielo.h"
#include <lauxlib.h>
#include <lua.h>

// Lua binding for cube()
static int l_cube(lua_State *L)
{
	float x = (float)luaL_checknumber(L, 1);
	lua_pushnumber(L, cube(x));
	return 1;
}

int luaopen_cielo(lua_State *L)
{
	static const luaL_Reg funcs[] = {{"cube", l_cube}, {NULL, NULL}};
	luaL_register(L, "cielo", funcs);
	return 1;
}
