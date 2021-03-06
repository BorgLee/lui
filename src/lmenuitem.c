static int l_uiMenuItemEnable(lua_State *L)
{
  uiMenuItemEnable(UI_CHECK_OBJECT(1, MenuItem));
  UI_RETURN_SELF;
}
static int l_uiMenuItemDisable(lua_State *L)
{
  uiMenuItemDisable(UI_CHECK_OBJECT(1, MenuItem));
  UI_RETURN_SELF;
}

static int l_uiMenuItemChecked(lua_State *L)
{
  if (lua_isnone(L, 2))
  {
    lua_pushboolean(L, uiMenuItemChecked(UI_CHECK_OBJECT(1, MenuItem)));
    return 1;
  }
  uiMenuItemSetChecked(UI_CHECK_OBJECT(1, MenuItem), luaL_checkboolean(L, 2));
  UI_RETURN_SELF;
}

static void on_menuitem_clicked(uiMenuItem *b, uiWindow* w, void *data)
{
  callback(data, b, "clicked");
}

static int l_uiMenuItemOnClicked(lua_State *L)
{
  //TODO:
  uiMenuItemOnClicked(UI_CHECK_OBJECT(1, MenuItem), on_menuitem_clicked, L);
  create_callback_data(L, 1, "clicked");
  UI_RETURN_SELF;
}

static struct luaL_Reg meta_MenuItem[] =
{
  { "Checked",              l_uiMenuItemChecked },
  { "OnClicked",            l_uiMenuItemOnClicked },

  CONTROL_COMMON_METAFIELD

  { "Enable",               l_uiMenuItemEnable },
  { "Disable",              l_uiMenuItemDisable },

  { NULL, NULL }
};
