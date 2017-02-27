static int l_uiNewHorizontalBox(lua_State *L)
{
  CREATE_OBJECT(Box, uiNewHorizontalBox());
  return 1;
}

static int l_uiNewVerticalBox(lua_State *L)
{
  CREATE_OBJECT(Box, uiNewVerticalBox());
  return 1;
}

static int l_uiBoxAppend(lua_State *L)
{
  int i;
  int stretchy = 0;
  int n = lua_gettop(L);
  uiBox *box = CAST_ARG(1, Box);
  uiControl *child = NULL;

  if (lua_isboolean(L, n))
  {
    stretchy = lua_toboolean(L, n);
    n = n - 1;
  }

  for (i = 2; i <= n; i++)
  {
    if (lua_isuserdata(L, i))
    {
      child = CAST_ARG(i, Control);
      uiBoxAppend(box, child, stretchy);
      lua_getmetatable(L, 1);
      lua_pushvalue(L, i);
      luaL_ref(L, -2);
    }
  }
  RETURN_SELF;
}

static int l_uiBoxDelete(lua_State *L)
{
  uiBoxDelete(CAST_ARG(1, Box), luaL_checkint(L, 2));
  RETURN_SELF;
}

static int l_uiBoxPadded(lua_State *L)
{
  if (lua_isnone(L, 2))
  {
    lua_pushboolean(L, uiBoxPadded(CAST_ARG(1, Box)));
    return 1;
  }
  uiBoxSetPadded(CAST_ARG(1, Box), luaL_checkboolean(L, 2));
  RETURN_SELF;
}

static struct luaL_Reg meta_Box[] =
{
  { "Append",               l_uiBoxAppend },
  { "Delete",               l_uiBoxDelete },
  { "Padded",               l_uiBoxPadded },

  CONTROL_COMMON_METAFIELD
  { NULL }
};
