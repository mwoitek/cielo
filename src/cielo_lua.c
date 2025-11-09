#include <lauxlib.h>
#include <lua.h>

#include "cielo.h"

// NOTE: this is not meant to be the final version of this function
static int l_rgb_from_hex(lua_State* L)
{
  const char* hex = luaL_checkstring(L, 1);

  bool ok = false;
  const Rgb rgb = rgb_from_hex(hex, &ok);
  if (!ok) return luaL_error(L, "invalid hex code: %s", hex);

  lua_createtable(L, 0, 3);

  lua_pushstring(L, "r");
  lua_pushnumber(L, rgb.r);
  lua_rawset(L, -3);

  lua_pushstring(L, "g");
  lua_pushnumber(L, rgb.g);
  lua_rawset(L, -3);

  lua_pushstring(L, "b");
  lua_pushnumber(L, rgb.b);
  lua_rawset(L, -3);

  return 1;
}

static const luaL_Reg funcs[] = {
    {"rgb_from_hex", l_rgb_from_hex},
    {          NULL,           NULL}
};

int luaopen_cielo(lua_State* L)
{
  luaL_register(L, "cielo", funcs);
  return 1;
}
