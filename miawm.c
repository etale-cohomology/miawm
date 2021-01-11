/*
t gcc-8  miawm.c -o miawm  $cflags $cnopie  -lxcb  &&  ./miawm
Xephyr -ac -screen 960x540 -reset -terminate :1  &
DISPLAY=:1 ./miawm

libxcb
libxcb-res

# BUGS
  - some "modern" apps (eg. Waterfox) start with a 2-dim of (1,1)... they expect too much baby-sitting from the wm!
*/
#include "miawm_util.c"

#define WM_SHORTCUTS_NDIM_X  ((XCB_MOD_MASK_SHIFT|XCB_MOD_MASK_LOCK|XCB_MOD_MASK_CONTROL|XCB_MOD_MASK_1|XCB_MOD_MASK_2|XCB_MOD_MASK_3|XCB_MOD_MASK_4|XCB_MOD_MASK_5) + 1)
#define WM_SHORTCUTS_NDIM_Y  (0xff + 1)
#define WM_SHORTCUTS_IDIM    (WM_SHORTCUTS_NDIM_X*WM_SHORTCUTS_NDIM_Y)

struct wm_t;  typedef  struct wm_t  wm_t;


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk0  mia_xcb */
#include <xcb/xcb.h>
#include <xcb/res.h>  // @xcb_res_query_client_ids()

minternal char* XCB_LUT_ERRORS_CSTR[]  = {[XCB_REQUEST]="XCB_REQUEST",[XCB_VALUE]="XCB_VALUE",[XCB_WINDOW]="XCB_WINDOW",[XCB_PIXMAP]="XCB_PIXMAP",[XCB_ATOM]="XCB_ATOM",[XCB_CURSOR]="XCB_CURSOR",[XCB_FONT]="XCB_FONT",[XCB_MATCH]="XCB_MATCH",[XCB_DRAWABLE]="XCB_DRAWABLE",[XCB_ACCESS]="XCB_ACCESS",[XCB_ALLOC]="XCB_ALLOC",[XCB_COLORMAP]="XCB_COLORMAP",[XCB_G_CONTEXT]="XCB_G_CONTEXT",[XCB_ID_CHOICE]="XCB_ID_CHOICE",[XCB_NAME]="XCB_NAME",[XCB_LENGTH]="XCB_LENGTH",[XCB_IMPLEMENTATION]="XCB_IMPLEMENTATION"};
minternal char* XCB_LUT_OPCODES_CSTR[] = {[XCB_CREATE_WINDOW]="XCB_CREATE_WINDOW",[XCB_CHANGE_WINDOW_ATTRIBUTES]="XCB_CHANGE_WINDOW_ATTRIBUTES",[XCB_GET_WINDOW_ATTRIBUTES]="XCB_GET_WINDOW_ATTRIBUTES",[XCB_DESTROY_WINDOW]="XCB_DESTROY_WINDOW",[XCB_DESTROY_SUBWINDOWS]="XCB_DESTROY_SUBWINDOWS",[XCB_CHANGE_SAVE_SET]="XCB_CHANGE_SAVE_SET",[XCB_REPARENT_WINDOW]="XCB_REPARENT_WINDOW",[XCB_MAP_WINDOW]="XCB_MAP_WINDOW",[XCB_MAP_SUBWINDOWS]="XCB_MAP_SUBWINDOWS",[XCB_UNMAP_WINDOW]="XCB_UNMAP_WINDOW",[XCB_UNMAP_SUBWINDOWS]="XCB_UNMAP_SUBWINDOWS",[XCB_CONFIGURE_WINDOW]="XCB_CONFIGURE_WINDOW",[XCB_CIRCULATE_WINDOW]="XCB_CIRCULATE_WINDOW",[XCB_GET_GEOMETRY]="XCB_GET_GEOMETRY",[XCB_QUERY_TREE]="XCB_QUERY_TREE",[XCB_INTERN_ATOM]="XCB_INTERN_ATOM",[XCB_GET_ATOM_NAME]="XCB_GET_ATOM_NAME",[XCB_CHANGE_PROPERTY]="XCB_CHANGE_PROPERTY",[XCB_DELETE_PROPERTY]="XCB_DELETE_PROPERTY",[XCB_GET_PROPERTY]="XCB_GET_PROPERTY",[XCB_LIST_PROPERTIES]="XCB_LIST_PROPERTIES",[XCB_SET_SELECTION_OWNER]="XCB_SET_SELECTION_OWNER",[XCB_GET_SELECTION_OWNER]="XCB_GET_SELECTION_OWNER",[XCB_CONVERT_SELECTION]="XCB_CONVERT_SELECTION",[XCB_SEND_EVENT]="XCB_SEND_EVENT",[XCB_GRAB_POINTER]="XCB_GRAB_POINTER",[XCB_UNGRAB_POINTER]="XCB_UNGRAB_POINTER",[XCB_GRAB_BUTTON]="XCB_GRAB_BUTTON",[XCB_UNGRAB_BUTTON]="XCB_UNGRAB_BUTTON",[XCB_CHANGE_ACTIVE_POINTER_GRAB]="XCB_CHANGE_ACTIVE_POINTER_GRAB",[XCB_GRAB_KEYBOARD]="XCB_GRAB_KEYBOARD",[XCB_UNGRAB_KEYBOARD]="XCB_UNGRAB_KEYBOARD",[XCB_GRAB_KEY]="XCB_GRAB_KEY",[XCB_UNGRAB_KEY]="XCB_UNGRAB_KEY",[XCB_ALLOW_EVENTS]="XCB_ALLOW_EVENTS",[XCB_GRAB_SERVER]="XCB_GRAB_SERVER",[XCB_UNGRAB_SERVER]="XCB_UNGRAB_SERVER",[XCB_QUERY_POINTER]="XCB_QUERY_POINTER",[XCB_GET_MOTION_EVENTS]="XCB_GET_MOTION_EVENTS",[XCB_TRANSLATE_COORDINATES]="XCB_TRANSLATE_COORDINATES",[XCB_WARP_POINTER]="XCB_WARP_POINTER",[XCB_SET_INPUT_FOCUS]="XCB_SET_INPUT_FOCUS",[XCB_GET_INPUT_FOCUS]="XCB_GET_INPUT_FOCUS",[XCB_QUERY_KEYMAP]="XCB_QUERY_KEYMAP",[XCB_OPEN_FONT]="XCB_OPEN_FONT",[XCB_CLOSE_FONT]="XCB_CLOSE_FONT",[XCB_QUERY_FONT]="XCB_QUERY_FONT",[XCB_QUERY_TEXT_EXTENTS]="XCB_QUERY_TEXT_EXTENTS",[XCB_LIST_FONTS]="XCB_LIST_FONTS",[XCB_LIST_FONTS_WITH_INFO]="XCB_LIST_FONTS_WITH_INFO",[XCB_SET_FONT_PATH]="XCB_SET_FONT_PATH",[XCB_GET_FONT_PATH]="XCB_GET_FONT_PATH",[XCB_CREATE_PIXMAP]="XCB_CREATE_PIXMAP",[XCB_FREE_PIXMAP]="XCB_FREE_PIXMAP",[XCB_CREATE_GC]="XCB_CREATE_GC",[XCB_CHANGE_GC]="XCB_CHANGE_GC",[XCB_COPY_GC]="XCB_COPY_GC",[XCB_SET_DASHES]="XCB_SET_DASHES",[XCB_SET_CLIP_RECTANGLES]="XCB_SET_CLIP_RECTANGLES",[XCB_FREE_GC]="XCB_FREE_GC",[XCB_CLEAR_AREA]="XCB_CLEAR_AREA",[XCB_COPY_AREA]="XCB_COPY_AREA",[XCB_COPY_PLANE]="XCB_COPY_PLANE",[XCB_POLY_POINT]="XCB_POLY_POINT",[XCB_POLY_LINE]="XCB_POLY_LINE",[XCB_POLY_SEGMENT]="XCB_POLY_SEGMENT",[XCB_POLY_RECTANGLE]="XCB_POLY_RECTANGLE",[XCB_POLY_ARC]="XCB_POLY_ARC",[XCB_FILL_POLY]="XCB_FILL_POLY",[XCB_POLY_FILL_RECTANGLE]="XCB_POLY_FILL_RECTANGLE",[XCB_POLY_FILL_ARC]="XCB_POLY_FILL_ARC",[XCB_PUT_IMAGE]="XCB_PUT_IMAGE",[XCB_GET_IMAGE]="XCB_GET_IMAGE",[XCB_POLY_TEXT_8]="XCB_POLY_TEXT_8",[XCB_POLY_TEXT_16]="XCB_POLY_TEXT_16",[XCB_IMAGE_TEXT_8]="XCB_IMAGE_TEXT_8",[XCB_IMAGE_TEXT_16]="XCB_IMAGE_TEXT_16",[XCB_CREATE_COLORMAP]="XCB_CREATE_COLORMAP",[XCB_FREE_COLORMAP]="XCB_FREE_COLORMAP",[XCB_COPY_COLORMAP_AND_FREE]="XCB_COPY_COLORMAP_AND_FREE",[XCB_INSTALL_COLORMAP]="XCB_INSTALL_COLORMAP",[XCB_UNINSTALL_COLORMAP]="XCB_UNINSTALL_COLORMAP",[XCB_LIST_INSTALLED_COLORMAPS]="XCB_LIST_INSTALLED_COLORMAPS",[XCB_ALLOC_COLOR]="XCB_ALLOC_COLOR",[XCB_ALLOC_NAMED_COLOR]="XCB_ALLOC_NAMED_COLOR",[XCB_ALLOC_COLOR_CELLS]="XCB_ALLOC_COLOR_CELLS",[XCB_ALLOC_COLOR_PLANES]="XCB_ALLOC_COLOR_PLANES",[XCB_FREE_COLORS]="XCB_FREE_COLORS",[XCB_STORE_COLORS]="XCB_STORE_COLORS",[XCB_STORE_NAMED_COLOR]="XCB_STORE_NAMED_COLOR",[XCB_QUERY_COLORS]="XCB_QUERY_COLORS",[XCB_LOOKUP_COLOR]="XCB_LOOKUP_COLOR",[XCB_CREATE_CURSOR]="XCB_CREATE_CURSOR",[XCB_CREATE_GLYPH_CURSOR]="XCB_CREATE_GLYPH_CURSOR",[XCB_FREE_CURSOR]="XCB_FREE_CURSOR",[XCB_RECOLOR_CURSOR]="XCB_RECOLOR_CURSOR",[XCB_QUERY_BEST_SIZE]="XCB_QUERY_BEST_SIZE",[XCB_QUERY_EXTENSION]="XCB_QUERY_EXTENSION",[XCB_LIST_EXTENSIONS]="XCB_LIST_EXTENSIONS",[XCB_CHANGE_KEYBOARD_MAPPING]="XCB_CHANGE_KEYBOARD_MAPPING",[XCB_GET_KEYBOARD_MAPPING]="XCB_GET_KEYBOARD_MAPPING",[XCB_CHANGE_KEYBOARD_CONTROL]="XCB_CHANGE_KEYBOARD_CONTROL",[XCB_GET_KEYBOARD_CONTROL]="XCB_GET_KEYBOARD_CONTROL",[XCB_BELL]="XCB_BELL",[XCB_CHANGE_POINTER_CONTROL]="XCB_CHANGE_POINTER_CONTROL",[XCB_GET_POINTER_CONTROL]="XCB_GET_POINTER_CONTROL",[XCB_SET_SCREEN_SAVER]="XCB_SET_SCREEN_SAVER",[XCB_GET_SCREEN_SAVER]="XCB_GET_SCREEN_SAVER",[XCB_CHANGE_HOSTS]="XCB_CHANGE_HOSTS",[XCB_LIST_HOSTS]="XCB_LIST_HOSTS",[XCB_SET_ACCESS_CONTROL]="XCB_SET_ACCESS_CONTROL",[XCB_SET_CLOSE_DOWN_MODE]="XCB_SET_CLOSE_DOWN_MODE",[XCB_KILL_CLIENT]="XCB_KILL_CLIENT",[XCB_ROTATE_PROPERTIES]="XCB_ROTATE_PROPERTIES",[XCB_FORCE_SCREEN_SAVER]="XCB_FORCE_SCREEN_SAVER",[XCB_SET_POINTER_MAPPING]="XCB_SET_POINTER_MAPPING",[XCB_GET_POINTER_MAPPING]="XCB_GET_POINTER_MAPPING"};
#define xcb_show_error(ERR)  printf("\x1b[91mFAIL  \x1b[31m%s\x1b[91m:\x1b[32m%d\x1b[91m:\x1b[94m%s  \x1b[0merror \x1b[0m%2d\x1b[91m:\x1b[33m%s  \x1b[0mop \x1b[0m%2d.%d\x1b[91m:\x1b[33m%s  \x1b[0mresource \x1b[35m%08x\x1b[0m\n", __FILE__,__LINE__,__func__, (ERR)->error_code,XCB_LUT_ERRORS_CSTR[(ERR)->error_code], (ERR)->major_code,(ERR)->minor_code,XCB_LUT_OPCODES_CSTR[(ERR)->major_code], (ERR)->resource_id)
#define xcb_chk(CONNECTION,COOKIE)  do{  /*@xcb_request_check() returns NULL @ error*/  \
  typeof(COOKIE) _cookie0 = (COOKIE);                                                   \
  xcb_void_cookie_t    _cookie1 = *(xcb_void_cookie_t*)&_cookie0;                       \
  xcb_generic_error_t* _st      = xcb_request_check((CONNECTION),_cookie1);             \
  if(_st!=NULL){ xcb_show_error(_st); free(_st); }                                      \
}while(0)

fdef xcb_screen_t* xcb_get_screen(xcb_connection_t* connection, int screen_idx){  // Return a screen from its number!
  const xcb_setup_t* setup = xcb_get_setup(connection);
  for(xcb_screen_iterator_t screen_it = xcb_setup_roots_iterator(setup);  screen_it.rem;  --screen_idx, xcb_screen_next(&screen_it))
    if(screen_idx==0) return screen_it.data;
  return NULL;
}

fdef xcb_map_state_t xcb_get_map_state(xcb_connection_t* connection, xcb_window_t window){  if(window==0x00000000) return 0;  // NOTE! This function is against the XCB philosophy because it's SYNC! Use it as a hack.
  xcb_get_window_attributes_reply_t* attr_reply = xcb_get_window_attributes_reply(connection, xcb_get_window_attributes_unchecked(connection, window), NULL);  if(attr_reply==NULL) return 0;
  xcb_map_state_t map_state = attr_reply->map_state;  // map_state: {XCB_MAP_STATE_UNMAPPED, XCB_MAP_STATE_UNVIEWABLE, XCB_MAP_STATE_VIEWABLE}
  free(attr_reply);
  return map_state;
}

fdef u16 xcb_get_pointer_mask(xcb_connection_t* connection, xcb_window_t window){
  xcb_query_pointer_reply_t* pointer_reply = xcb_query_pointer_reply(connection, xcb_query_pointer_unchecked(connection, window), NULL);  if(pointer_reply==NULL) return 0x00;
  u16 pointer_mask = pointer_reply->mask;  // printf("state \x1b[37m%04x  \x1b[0m\n", pointer_reply->mask);
  free(pointer_reply);
  return pointer_mask;
}

fdef xcb_keycode_t* xcb_get_modmap(xcb_connection_t* connection){
  xcb_get_modifier_mapping_reply_t* mapping  = xcb_get_modifier_mapping_reply(connection, xcb_get_modifier_mapping_unchecked(connection), NULL);
  xcb_keycode_t*                    keycodes = xcb_get_modifier_mapping_keycodes(mapping);
  xcb_keycode_t*                    modmap   = vec_ini(xcb_keycode_t);
  m_fori(i, 0,xcb_get_modifier_mapping_keycodes_length(mapping))
    vec_push(modmap, keycodes[i]);
  free(mapping);
  return modmap;
}

fdef xcb_atom_t xcb_property_name_to_atom(xcb_connection_t* connection, char* property_name){  // x11 property: name to atom!
  xcb_intern_atom_reply_t* atom_reply    = xcb_intern_atom_reply(connection, xcb_intern_atom_unchecked(connection, 0/*even if nexists*/, strlen(property_name),property_name), NULL);
  xcb_atom_t               property_atom = atom_reply->atom;
  free(atom_reply);
  return property_atom;
}

fdefi u32 xcb_color(xcb_screen_t* screen, u32 rgb){  return screen->root_depth==16 ? rgb888_to_bgr565(rgb) : rgb888_to_bgr888(rgb);  }


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk0  mia_wm */
struct wm_t{
  xcb_connection_t* connection;
  int               screen_idx;
  u16               screen_ndim_x, screen_ndim_y;
  xcb_screen_t*     screen;

  i32               shortcuts_ndim_x, shortcuts_ndim_y;
  void              (*shortcuts[WM_SHORTCUTS_NDIM_X][WM_SHORTCUTS_NDIM_Y])(wm_t*);

  xcb_window_t*     windows;  // the vector of windows managed by `miawm`!
  xcb_window_t      menu;     // the window that displays all windows as a menu (or as thumbnails)!
  xcb_window_t      focus;    // the window in focus!

  xcb_drawable_t    menu_backbuf;
  u16               menu_ndim_x, menu_ndim_y;
  xcb_font_t        font;
  xcb_gcontext_t    font_gc_dark, font_gc_light;
  u16               font_ndim_x,  font_ndim_y;

  xcb_keycode_t*    modmap;  // keycodes of the 8 X11 modifiers!

  int               running;
};

fdef wm_t wm_ini(i32 shortcuts_ndim_x,i32 shortcuts_ndim_y,void (*shortcuts[WM_SHORTCUTS_NDIM_X][WM_SHORTCUTS_NDIM_Y])(wm_t*), char* font_name,u16 font_ndim_x,u16 font_ndim_y, u16 wm_menu_ndim_x){
  wm_t wm          = {};
  wm.connection    = xcb_connect(NULL,&wm.screen_idx);  if(xcb_connection_has_error(wm.connection)){  printf("\x1b[91mFAIL  \x1b[31m%s\x1b[91m:\x1b[32m%d\x1b[91m:\x1b[94m%s\x1b[0m()  \x1b[35m%s\x1b[0m()  \x1b[0m%s\n", __FILE__,__LINE__,__func__, "xcb_connect","Can't xcb_connect() to the X server");  exit(1);  }
  wm.screen        = xcb_get_screen(wm.connection, wm.screen_idx);
  wm.screen_ndim_x = wm.screen->width_in_pixels;
  wm.screen_ndim_y = wm.screen->height_in_pixels;
  xcb_generic_error_t* wm_st = xcb_request_check(wm.connection, xcb_change_window_attributes_checked(wm.connection,wm.screen->root, XCB_CW_EVENT_MASK,(u32[]){XCB_EVENT_MASK_KEY_PRESS|XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_STRUCTURE_NOTIFY|XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY|XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT|XCB_EVENT_MASK_PROPERTY_CHANGE}));  if(wm_st!=NULL){ xcb_show_error(wm_st); free(wm_st); exit(1); }

  // ----------------------------------------------------------------
  wm.shortcuts_ndim_x = shortcuts_ndim_x;
  wm.shortcuts_ndim_y = shortcuts_ndim_y;
  memcpy(wm.shortcuts, shortcuts, sizeof(wm.shortcuts[0][0])*wm.shortcuts_ndim_x*wm.shortcuts_ndim_y);  // wm.shortcuts = shortcuts;  // TODO! We must copy the WHOLE array if we want to keep the nice 2-array syntax? Yuck!
  m_fori(mod, 0,wm.shortcuts_ndim_x)
    m_fori(key, 0,wm.shortcuts_ndim_y)
      if(wm.shortcuts[mod][key]!=NULL)  xcb_grab_key(wm.connection,1, wm.screen->root, mod,key, XCB_GRAB_MODE_ASYNC,XCB_GRAB_MODE_ASYNC);  // XCB_MOD_MASK_ANY XCB_GRAB_ANY

  // ----------------------------------------------------------------
  wm.windows = vec_ini(xcb_window_t);
  xcb_query_tree_reply_t* tree_reply = xcb_query_tree_reply(wm.connection, xcb_query_tree_unchecked(wm.connection, wm.screen->root), NULL);  // Get root window, parent window, and list of generation 1 child windows. The children are listed in bottom-to-top stacking order!
  xcb_window_t*           children   = xcb_query_tree_children(tree_reply);
  m_fori(i, 0,tree_reply->children_len)
    if(children[i]!=wm.menu)  vec_push(wm.windows, children[i]);
  free(tree_reply);

  // ----------------------------------------------------------------
  wm.menu        = xcb_generate_id(wm.connection);
  wm.menu_ndim_x = m_min(wm_menu_ndim_x,wm.screen->width_in_pixels);
  xcb_create_window(wm.connection, wm.screen->root_depth, wm.menu, wm.screen->root, 0,0,wm.menu_ndim_x,font_ndim_y, 1,XCB_WINDOW_CLASS_INPUT_OUTPUT, XCB_COPY_FROM_PARENT, XCB_CW_BACK_PIXMAP|XCB_CW_BORDER_PIXEL,(u32[]){XCB_BACK_PIXMAP_NONE,xcb_color(wm.screen,0xa0a0a0)});
  xcb_configure_window(wm.connection, wm.menu, XCB_CONFIG_WINDOW_BORDER_WIDTH, (u32[]){1});

  // ----------------------------------------------------------------
  wm.menu_backbuf  = xcb_generate_id(wm.connection);
  wm.font          = xcb_generate_id(wm.connection);
  wm.font_gc_dark  = xcb_generate_id(wm.connection);
  wm.font_gc_light = xcb_generate_id(wm.connection);
  wm.font_ndim_x   = font_ndim_x;
  wm.font_ndim_y   = font_ndim_y;
  xcb_create_pixmap(wm.connection, wm.screen->root_depth, wm.menu_backbuf, wm.screen->root, wm.menu_ndim_x,wm.screen->height_in_pixels);
  xcb_open_font(wm.connection, wm.font, strlen(font_name),font_name);  // *_checked() functions FLUSH errors (and so BLOCK), forcing them to come!
  xcb_create_gc(wm.connection, wm.font_gc_dark,  wm.screen->root, XCB_GC_FOREGROUND|XCB_GC_BACKGROUND|XCB_GC_FONT|XCB_GC_GRAPHICS_EXPOSURES, (u32[]){xcb_color(wm.screen,0xffffff), xcb_color(wm.screen,0x101010), wm.font, XCB_EXPOSURES_NOT_ALLOWED});
  xcb_create_gc(wm.connection, wm.font_gc_light, wm.screen->root, XCB_GC_FOREGROUND|XCB_GC_BACKGROUND|XCB_GC_FONT|XCB_GC_GRAPHICS_EXPOSURES, (u32[]){xcb_color(wm.screen,0x101010), xcb_color(wm.screen,0xf0f0f0), wm.font, XCB_EXPOSURES_NOT_ALLOWED});

  // ----------------------------------------------------------------
  wm.modmap  = xcb_get_modmap(wm.connection);
  wm.running = 1;
  signal(SIGCHLD, SIG_IGN);  // Now our children won't become zombies if we don't @wait()/@waitpid() on them!
  xcb_flush(wm.connection);
  return wm;
}

fdef void wm_end(wm_t* wm){
  vec_end(wm->modmap);
  xcb_free_pixmap(wm->connection, wm->menu_backbuf);
  xcb_close_font(wm->connection, wm->font);
  xcb_free_gc(wm->connection, wm->font_gc_dark);
  xcb_free_gc(wm->connection, wm->font_gc_light);
  vec_end(wm->windows);
  xcb_destroy_window(wm->connection, wm->menu);
  m_fori(mod, 0,wm->shortcuts_ndim_x)
    m_fori(key, 0,wm->shortcuts_ndim_y)
      if(wm->shortcuts[mod][key]!=NULL)  xcb_ungrab_key(wm->connection, key, wm->screen->root, mod);
  xcb_disconnect(wm->connection);
}

fdef void wm_menu_hide(wm_t* wm){
  xcb_unmap_window(wm->connection, wm->menu);
  if(wm->focus!=0x00000000)
    xcb_configure_window(wm->connection, wm->focus, XCB_CONFIG_WINDOW_BORDER_WIDTH, (u32[]){0});
}

fdef void wm_menu_show(wm_t* wm){  // 1ms
  wm->menu_ndim_y = m_max((vec_idim(wm->windows)*wm->font_ndim_y), 1);
  xcb_grab_server(wm->connection);
  if(xcb_get_map_state(wm->connection,wm->menu)!=XCB_MAP_STATE_VIEWABLE) xcb_map_window(wm->connection, wm->menu);
  xcb_configure_window(wm->connection, wm->menu, XCB_CONFIG_WINDOW_X|XCB_CONFIG_WINDOW_Y|XCB_CONFIG_WINDOW_WIDTH|XCB_CONFIG_WINDOW_HEIGHT | XCB_CONFIG_WINDOW_STACK_MODE,(u32[]){wm->screen_ndim_x/2 - wm->menu_ndim_x/2, wm->screen_ndim_y/2 - wm->menu_ndim_y/2, wm->menu_ndim_x,wm->menu_ndim_y, XCB_STACK_MODE_ABOVE});  // xcb_poly_fill_rectangle(wm->connection, wm->menu_backbuf, wm->font_gc_light, 1,(xcb_rectangle_t[]){{0,0, wm->menu_ndim_x,wm->menu_ndim_y}});  // clear backbuffer!

  // ----------------------------------------------------------------
  xcb_atom_t wm_name_property_atom      = xcb_property_name_to_atom(wm->connection,"WM_NAME");
  xcb_atom_t wm_name_property_type_atom = XCB_ATOM_STRING;
  u32        wm_name_property_length    = 0x40;  // in 4-byte chunks!

  xcb_get_geometry_cookie_t*          win_geoms_cookies            = alloca(sizeof(xcb_get_geometry_cookie_t)         *vec_idim(wm->windows));
  xcb_get_window_attributes_cookie_t* win_attrs_cookies            = alloca(sizeof(xcb_get_window_attributes_cookie_t)*vec_idim(wm->windows));
  xcb_query_tree_cookie_t*            win_tree_cookies             = alloca(sizeof(xcb_query_tree_cookie_t)           *vec_idim(wm->windows));
  xcb_res_query_client_ids_cookie_t*  client_ids_cookies           = alloca(sizeof(xcb_res_query_client_ids_cookie_t) *vec_idim(wm->windows));
  xcb_get_property_cookie_t*          wm_name_property_cookies     = alloca(sizeof(xcb_get_property_cookie_t)         *vec_idim(wm->windows));
  m_fori(i, 0,vec_idim(wm->windows)){
    win_geoms_cookies[i]            = xcb_get_geometry_unchecked(         wm->connection, wm->windows[i]);
    win_attrs_cookies[i]            = xcb_get_window_attributes_unchecked(wm->connection, wm->windows[i]);
    win_tree_cookies[i]             = xcb_query_tree_unchecked(           wm->connection, wm->windows[i]);  // Get root window, parent window, and list of generation 1 child windows. The children are listed in bottom-to-top stacking order!
    client_ids_cookies[i]           = xcb_res_query_client_ids_unchecked(wm->connection, 1,(xcb_res_client_id_spec_t[]){{client:wm->windows[i], mask:XCB_RES_CLIENT_ID_MASK_LOCAL_CLIENT_PID}});  // NOTE! This particular API call DOES allow to query multiply windows/clients at once... but we don't do it for the sake of consistency!
    wm_name_property_cookies[i]     = xcb_get_property_unchecked(         wm->connection,0, wm->windows[i], wm_name_property_atom,wm_name_property_type_atom, 0,wm_name_property_length);
  }

  // ----------------------------------------------------------------
  m_fori(i, 0,vec_idim(wm->windows)){
    xcb_get_geometry_reply_t*          win_geom_reply = xcb_get_geometry_reply(wm->connection, win_geoms_cookies[i], NULL);
    xcb_get_window_attributes_reply_t* win_attr_reply = xcb_get_window_attributes_reply(wm->connection, win_attrs_cookies[i], NULL);  // map_state: {XCB_MAP_STATE_UNMAPPED, XCB_MAP_STATE_UNVIEWABLE, XCB_MAP_STATE_VIEWABLE}
    xcb_query_tree_reply_t*            win_tree_reply = xcb_query_tree_reply(wm->connection, win_tree_cookies[i], NULL);

    xcb_res_query_client_ids_reply_t*  client_ids_reply = xcb_res_query_client_ids_reply(wm->connection, client_ids_cookies[i], NULL);  // https://stackoverflow.com/questions/37283179  // https://unix.stackexchange.com/questions/5478/  // https://www.x.org/releases/X11R7.7/doc/resourceproto/resproto.txt
    xcb_res_client_id_value_iterator_t client_ids_it    = xcb_res_query_client_ids_ids_iterator(client_ids_reply);
    u32                                client_ids_value = *xcb_res_client_id_value_value(client_ids_it.data);  if(!(client_ids_it.data->spec.mask&XCB_RES_CLIENT_ID_MASK_LOCAL_CLIENT_PID)) client_ids_value = 0x00;

    xcb_get_property_reply_t* wm_name_property_reply = xcb_get_property_reply(wm->connection, wm_name_property_cookies[i], NULL);  if(wm_name_property_reply->type==0) m_fail();
    char*                     wm_name_property_value = (char*)xcb_get_property_value(wm_name_property_reply);

    char comm[TASK_COMM_LEN]; pid_comm(client_ids_value, TASK_COMM_LEN,comm);
    char title[0xff+1];  title[sizeof(title)-1]=0x00;  memset(title,0x20,sizeof(title)-1);
    int  title_len=snprintf(title,sizeof(title)-1, " %d %d  (%08x %6d)  (%08x %08x)  (%4d %4d)  (%4d %4d)  %2d  %-16s  %.*s", win_attr_reply->map_state,win_attr_reply->override_redirect, wm->windows[i],client_ids_value, win_tree_reply->root,win_tree_reply->parent, win_geom_reply->x,win_geom_reply->y, win_geom_reply->width,win_geom_reply->height, win_geom_reply->depth, comm, xcb_get_property_value_length(wm_name_property_reply),wm_name_property_value);  title[title_len]=0x20;

    xcb_image_text_8(wm->connection, wm->menu_ndim_x/wm->font_ndim_x, wm->menu_backbuf, wm->windows[i]==wm->focus ? wm->font_gc_light : wm->font_gc_dark, 0x00*wm->font_ndim_x, i*wm->font_ndim_y + wm->font_ndim_y, title);  // Draws fonts WITH background! xcb_image_text_8_checked() is slower because it BLOCKS (by flushing errors)!

    free(win_geom_reply);
    free(win_attr_reply);
    free(win_tree_reply);
    free(client_ids_reply);
    free(wm_name_property_reply);
  }

  // ----------------------------------------------------------------
  xcb_copy_area(wm->connection, wm->menu_backbuf, wm->menu, wm->font_gc_dark, 0,0, 0,0, wm->menu_ndim_x,wm->menu_ndim_y);  // blit backbuffer!
  xcb_ungrab_server(wm->connection);
}

fdef void wm_win_set_priority_least(wm_t* wm, xcb_window_t window){  // move @window to the least-priority position! O[n]
  if(wm->windows[0]==window) return;  // in this case, @window is already least-priority!
  int window_idx = vec_idx(wm->windows, window);  if(window_idx==-1) return;  // window doesn't exist!

  xcb_window_t prev = wm->windows[0];  // 0) shift by +1 all items from 0 until idx[window]-1 (ie. the item at idx[window] doesn't get shifted, but the previous item clobbers it)
  m_fori(i, 1,window_idx+1)
    xorswap(wm->windows[i], prev);

  wm->windows[0] = window;  // 1) put the cherry at the bottom
}

fdef void wm_win_set_priority_greatest(wm_t* wm, xcb_window_t window){  // move @window to the greatest-priority position! O[n]
  if(wm->windows[vec_idim(wm->windows)-1]==window) return;  // in this case, @window is already greatest-priority!
  int window_idx = vec_idx(wm->windows, window);  if(window_idx==-1) return;  // window doesn't exist!

  m_fori(i, window_idx+1,vec_idim(wm->windows))  // 0) shift by -1 all items from window_idx+1 until vec_idim(wm->windows)-1
    xorswap(wm->windows[i-1], wm->windows[i]);

  wm->windows[vec_idim(wm->windows)-1] = window;  // 1) put the cherry at the top
}

fdef void wm_focus_set(wm_t* wm, xcb_window_t window){  printf("  \x1b[33mFOCUS  \x1b[0mold \x1b[35m%08x  \x1b[0mnew \x1b[35m%08x\x1b[0m\n", wm->focus,window);  // NOTE! @window MUST be mapped, or @xcb_set_input_focus() generates an XCB error!
  if(wm->focus!=0x00000000 && vec_idx(wm->windows,wm->focus)!=-1)  xcb_configure_window(wm->connection, wm->focus, XCB_CONFIG_WINDOW_BORDER_WIDTH, (u32[]){0});
  if(xcb_get_pointer_mask(wm->connection,wm->screen->root)!=0x00)  xcb_configure_window(wm->connection, window, XCB_CONFIG_WINDOW_BORDER_WIDTH|XCB_CONFIG_WINDOW_STACK_MODE, (u32[]){2,XCB_STACK_MODE_ABOVE});
  else                                                             xcb_configure_window(wm->connection, window, XCB_CONFIG_WINDOW_STACK_MODE, (u32[]){XCB_STACK_MODE_ABOVE});
  xcb_set_input_focus(wm->connection, XCB_INPUT_FOCUS_POINTER_ROOT, window, XCB_CURRENT_TIME);  // NOTE! @window MUST be mapped, or @xcb_set_input_focus() generates an XCB error!
  wm->focus = window;
}

fdef void wm_focus_next(wm_t* wm, int idx){  // focus the window that is max[min[UV[i]], max[LV[i]]]  (where: UV[i] is the upper-viewable chain at @i; LV[i] is the lower-viewable chain it @i; min[UV[i]] is the window in UV[i] whose index is minimum among all windows in UV[i]; max[LV[i]] is the window in LV[i] whose index is maximum among all windows in LV[i]
  wm->focus = 0x00000000;

  if(idx==-1) return;
  m_fori(i, idx+1,vec_idim(wm->windows)){  // 0) first search forwards!
    if(xcb_get_map_state(wm->connection, wm->windows[i])!=XCB_MAP_STATE_VIEWABLE)  continue;
    wm_focus_set(wm, wm->windows[i]);  // NOTE! @window MUST be mapped, or @xcb_set_input_focus() generates an XCB error!
    break;
  }

  if(wm->focus!=0x00000000) return;  // (if we've found what we want, then exit!)
  for(int i=idx-1; i>=0; --i){  // 1) then search backwards!
    if(xcb_get_map_state(wm->connection, wm->windows[i])!=XCB_MAP_STATE_VIEWABLE)  continue;
    wm_focus_set(wm, wm->windows[i]);  // NOTE! @window MUST be mapped, or @xcb_set_input_focus() generates an XCB error!
    break;
  }
}


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk0  mia_cmd */
fdef void cmd_win_grid(wm_t* wm, xcb_window_t window, int grid_npos_x,int grid_npos_y, int grid_ndim_x,int grid_ndim_y){  if(window==0x00000000) return;
  u32 win_npos_x = grid_npos_x*wm->screen_ndim_x / grid_ndim_x;
  u32 win_npos_y = grid_npos_y*wm->screen_ndim_y / grid_ndim_y;
  u32 win_ndim_x =           1*wm->screen_ndim_x / grid_ndim_x;
  u32 win_ndim_y =           1*wm->screen_ndim_y / grid_ndim_y;
  xcb_configure_window(wm->connection, window, XCB_CONFIG_WINDOW_X|XCB_CONFIG_WINDOW_Y|XCB_CONFIG_WINDOW_WIDTH|XCB_CONFIG_WINDOW_HEIGHT | XCB_CONFIG_WINDOW_BORDER_WIDTH|XCB_CONFIG_WINDOW_STACK_MODE, (u32[]){win_npos_x,win_npos_y,win_ndim_x,win_ndim_y, 2,XCB_STACK_MODE_ABOVE});
  xcb_warp_pointer(wm->connection,XCB_NONE,wm->screen->root,0,0,0,0, win_npos_x+win_ndim_x/2,win_npos_y+win_ndim_y/2);
  if(xcb_get_map_state(wm->connection,wm->menu)==XCB_MAP_STATE_VIEWABLE)  wm_menu_show(wm);
}

fdef void cmd_exec(wm_t* wm, char** args){  int pid=exec(args);  }  // printf("  \x1b[33mEXEC  \x1b[31m%d  \x1b[0m\n",pid);

fdef void cmd_exit(wm_t* wm){  wm->running = 0;  }

fdef void cmd_win_close(wm_t* wm, xcb_window_t window){  // https://nachtimwald.com/2009/11/08/sending-wm_delete_window-client-messages/
  xcb_client_message_event_t ev;  memset(&ev, 0x00, sizeof(xcb_client_message_event_t));
  ev.response_type  = XCB_CLIENT_MESSAGE;
  ev.format         = 32;  // wm_protocols_format
  ev.window         = window;
  ev.type           = xcb_property_name_to_atom(wm->connection, "WM_PROTOCOLS");      // wm_protocols_atom
  ev.data.data32[0] = xcb_property_name_to_atom(wm->connection, "WM_DELETE_WINDOW");  // wm_delete_window_atom
  ev.data.data32[1] = XCB_CURRENT_TIME;
  xcb_send_event(wm->connection, 0, window, XCB_EVENT_MASK_NO_EVENT, (const char*)&ev);  // 0) do cmd  // wm_menu_show(wm);  // BUG! Calling @wm_menu_show() here causes: spamming new windows (with key repeat) and closing them (with key repeat) causes a segfault in @wm_menu_show()
}

fdef void cmd_win_kill(wm_t* wm, xcb_window_t window, int sig){  if(window==0x00000000) return;  if(sig!=2 && sig!=9) return;  // NOTE! Don't @xcb_kill_client() because it doesn't kill the process, just its xcb_connection_t to X11! Then it becomes worse than a zombie!
  xcb_res_query_client_ids_reply_t*  client_ids_reply = xcb_res_query_client_ids_reply(wm->connection, xcb_res_query_client_ids_unchecked(wm->connection, 1,(xcb_res_client_id_spec_t[]){{client:window, mask:XCB_RES_CLIENT_ID_MASK_LOCAL_CLIENT_PID}}), NULL);  // https://stackoverflow.com/questions/37283179
  xcb_res_client_id_value_t*         client_ids_data  = xcb_res_query_client_ids_ids_iterator(client_ids_reply).data;
  u32 pid = *xcb_res_client_id_value_value(client_ids_data);  if(!(client_ids_data->spec.mask&XCB_RES_CLIENT_ID_MASK_LOCAL_CLIENT_PID)) return;
  free(client_ids_reply);
  m_chks(kill(pid, sig));  // 0) do cmd  // wm_menu_show(wm);  // BUG! Calling @wm_menu_show() here causes: spamming new windows (with key repeat) and closing them (with key repeat) causes a segfault in @wm_menu_show()
}

fdef void cmd_focus_hide(wm_t* wm){  if(wm->focus==0x00000000) return;
  xcb_unmap_window(wm->connection, wm->focus);                                         // 0) do cmd
  xcb_window_t window     = wm->focus;                                                 // 1) prep
  int          window_idx = vec_idx(wm->windows, window);  if(window_idx==-1) return;  // 1) prep
  wm_focus_next(wm, window_idx);                                                       // 2) focus the window that is max[min[UV[i]], max[LV[i]]]  (where: UV[i] is the upper-viewable chain at @i; LV[i] is the lower-viewable chain it @i; min[UV[i]] is the window in UV[i] whose index is minimum among all windows in UV[i]; max[LV[i]] is the window in LV[i] whose index is maximum among all windows in LV[i]
  wm_win_set_priority_least(wm, window);                                               // 3) modify the window stack: move the focus window to the least-priority position! O[n]
  wm_menu_show(wm);                                                                    // 4) render
}

fdef void cmd_focus_prev(wm_t* wm){  if(vec_idim(wm->windows)==0) return;  // NOTE! Here we don't care if the window we're about to focus is unmapped (we're gonna map it anyway)!
  int focus_idx = vec_idx(wm->windows, wm->focus);
  if(focus_idx==-1) focus_idx = vec_idim(wm->windows) - 1;  // pythonic indexing!
  else              focus_idx = m_max(focus_idx-1, 0);
  xcb_window_t window = wm->windows[focus_idx];
  xcb_map_window(wm->connection, window);
  wm_focus_set(wm, window);  // NOTE! @window MUST be mapped, or @xcb_set_input_focus() generates an XCB error!
  wm_menu_show(wm);
}

fdef void cmd_focus_next(wm_t* wm){  if(vec_idim(wm->windows)==0) return;  // NOTE! Here we don't care if the window we're about to focus is unmapped (we're gonna map it anyway)!
  int focus_idx = vec_idx(wm->windows, wm->focus);
  if(focus_idx==-1) focus_idx = vec_idim(wm->windows) - 1;  // pythonic indexing!
  else              focus_idx = m_min(focus_idx+1, vec_idim(wm->windows)-1);
  xcb_window_t window    = wm->windows[focus_idx];
  xcb_map_window(wm->connection, window);
  wm_focus_set(wm, window);  // NOTE! @window MUST be mapped, or @xcb_set_input_focus() generates an XCB error!
  wm_menu_show(wm);
}

fdef void cmd_noop(            wm_t* wm){  }
fdef void cmd_exec_ss(         wm_t* wm){  cmd_exec(wm, (char*[]){"/home/da/bin/sspng",                       NULL});  }
fdef void cmd_exec_alsamixer(  wm_t* wm){  cmd_exec(wm, (char*[]){"/usr/bin/urxvt", "-e", "alsamixer",        NULL});  }
fdef void cmd_exec_nav(        wm_t* wm){  cmd_exec(wm, (char*[]){"/usr/bin/urxvt", "-e", "mc",               NULL});  }
fdef void cmd_exec_web(        wm_t* wm){  cmd_exec(wm, (char*[]){"/home/da/dl/deb/waterfox/waterfox",        NULL});  }
fdef void cmd_exec_txt(        wm_t* wm){  cmd_exec(wm, (char*[]){"/home/da/git/sublime_text_3/sublime_text", NULL});  }
fdef void cmd_exec_term(       wm_t* wm){  cmd_exec(wm, (char*[]){"/usr/bin/urxvt",                           NULL});  }
fdef void cmd_exec_mon(        wm_t* wm){  cmd_exec(wm, (char*[]){"/home/da/bin/loop",                        NULL});  }
fdef void cmd_focus_close(     wm_t* wm){  cmd_win_close(wm, wm->focus);  }
fdef void cmd_focus_kill2(     wm_t* wm){  cmd_win_kill(wm, wm->focus, 2);  }  // NOTE! Don't @xcb_kill_client() because it doesn't kill the process, just its xcb_connection_t to X11! Then it becomes worse than a zombie!
fdef void cmd_focus_kill9(     wm_t* wm){  cmd_win_kill(wm, wm->focus, 9);  }  // NOTE! Don't @xcb_kill_client() because it doesn't kill the process, just its xcb_connection_t to X11! Then it becomes worse than a zombie!
fdef void cmd_focus_grid_00_22(wm_t* wm){  cmd_win_grid(wm, wm->focus, 0,0, 2,2);  }
fdef void cmd_focus_grid_10_22(wm_t* wm){  cmd_win_grid(wm, wm->focus, 1,0, 2,2);  }
fdef void cmd_focus_grid_00_21(wm_t* wm){  cmd_win_grid(wm, wm->focus, 0,0, 2,1);  }
fdef void cmd_focus_grid_00_11(wm_t* wm){  cmd_win_grid(wm, wm->focus, 0,0, 1,1);  }
fdef void cmd_focus_grid_01_22(wm_t* wm){  cmd_win_grid(wm, wm->focus, 0,1, 2,2);  }
fdef void cmd_focus_grid_11_22(wm_t* wm){  cmd_win_grid(wm, wm->focus, 1,1, 2,2);  }
fdef void cmd_focus_grid_10_21(wm_t* wm){  cmd_win_grid(wm, wm->focus, 1,0, 2,1);  }
fdef void cmd_focus_grid_00_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 0,0, 4,4);  }
fdef void cmd_focus_grid_10_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 1,0, 4,4);  }
fdef void cmd_focus_grid_20_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 2,0, 4,4);  }
fdef void cmd_focus_grid_30_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 3,0, 4,4);  }
fdef void cmd_focus_grid_01_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 0,1, 4,4);  }
fdef void cmd_focus_grid_11_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 1,1, 4,4);  }
fdef void cmd_focus_grid_21_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 2,1, 4,4);  }
fdef void cmd_focus_grid_31_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 3,1, 4,4);  }
fdef void cmd_focus_grid_02_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 0,2, 4,4);  }
fdef void cmd_focus_grid_12_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 1,2, 4,4);  }
fdef void cmd_focus_grid_22_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 2,2, 4,4);  }
fdef void cmd_focus_grid_32_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 3,2, 4,4);  }
fdef void cmd_focus_grid_03_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 0,3, 4,4);  }
fdef void cmd_focus_grid_13_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 1,3, 4,4);  }
fdef void cmd_focus_grid_23_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 2,3, 4,4);  }
fdef void cmd_focus_grid_33_44(wm_t* wm){  cmd_win_grid(wm, wm->focus, 3,3, 4,4);  }


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk0  mia_ev: event loop & event handlers! */
fdef void ev_error(wm_t* wm, xcb_generic_error_t* ev){  xcb_show_error(ev);  }

fdef void ev_key_press(wm_t* wm, xcb_key_press_event_t* ev){  // printf("\x1b[0m%-18s  \x1b[0mkey \x1b[94m0x\x1b[35m%02x\x1b[91m:\x1b[94m0d\x1b[35m%03d  \x1b[0mmod \x1b[37m%04x  \x1b[0m\n", "XCB_KEY_PRESS", ev->detail,ev->detail, ev->state);
  void (*cmd)(wm_t*) = wm->shortcuts[ev->state][ev->detail];  if(cmd==NULL) return;
  cmd(wm);
}

fdef void ev_key_release(wm_t* wm, xcb_key_release_event_t* ev){  // printf("\x1b[0m%-18s  \x1b[0mkey \x1b[94m0x\x1b[35m%02x\x1b[91m:\x1b[94m0d\x1b[35m%03d  \x1b[0mmod \x1b[37m%04x  \x1b[0m", "XCB_KEY_RELEASE", ev->detail,ev->detail, ev->state);
  int is_mod = 0;  vec_forall(wm->modmap,it) is_mod |= ev->detail==*it;  // printf("\x1b[92m%d  \x1b[0m\n", is_mod);  // m_fori(i, 0,vec_idim(wm->modmap)) printf(" %02x",wm->modmap[i]);  putchar(0x0a);
  if(is_mod || ev->state==0x00){
    wm_menu_hide(wm);
    wm_win_set_priority_greatest(wm,wm->focus);
  }
}

fdef void ev_focus_in(wm_t* wm, xcb_focus_in_event_t* ev){  // printf("\x1b[92m%-18s  \x1b[0mwin \x1b[35m%08x  \x1b[0mdetail \x1b[32m%x  \x1b[0mmode \x1b[94m%x  \x1b[0m\n", "XCB_FOCUS_IN",  ev->event, ev->detail, ev->mode);
  if(ev->event==wm->menu || ev->event==wm->focus || ev->detail!=XCB_NOTIFY_DETAIL_NONLINEAR) return;
  if(vec_idx(wm->windows,ev->event)==-1) return;
  if(xcb_get_map_state(wm->connection,ev->event)!=XCB_MAP_STATE_VIEWABLE)  xcb_map_window(wm->connection, ev->event);
  xcb_configure_window(wm->connection, ev->event, XCB_CONFIG_WINDOW_STACK_MODE, (u32[]){XCB_STACK_MODE_ABOVE});
  wm_menu_hide(wm);
  wm_win_set_priority_greatest(wm,ev->event);
  wm->focus = ev->event;
}

fdef void ev_create_notify(wm_t* wm, xcb_create_notify_event_t* ev){  // printf("\x1b[92m%-18s  \x1b[0mwin \x1b[35m%08x  \x1b[0m\n", "XCB_CREATE_NOTIFY",ev->window);
  if(ev->window==wm->menu) return;
}

fdef void ev_destroy_notify(wm_t* wm, xcb_destroy_notify_event_t* ev){  // printf("\x1b[92m%-18s  \x1b[0mwin \x1b[35m%08x  \x1b[0mfocus \x1b[33m%08x  \x1b[0m\n", "XCB_DESTROY_NOTIFY",ev->window, wm->focus);
  if(ev->window==wm->menu) return;
  int window_idx = vec_idx(wm->windows, ev->window);  if(window_idx==-1) return;      // 1) prep
  wm_focus_next(wm, window_idx);                                                      // 2) focus the window that is max[min[UV[i]], max[LV[i]]]  (where: UV[i] is the upper-viewable chain at @i; LV[i] is the lower-viewable chain it @i; min[UV[i]] is the window in UV[i] whose index is minimum among all windows in UV[i]; max[LV[i]] is the window in LV[i] whose index is maximum among all windows in LV[i]
  vec_del(wm->windows, window_idx);                                                   // 3) modify the window stack: delete the destroyed window
  if(xcb_get_pointer_mask(wm->connection,wm->screen->root)!=0x00)  wm_menu_show(wm);  // 4) render
}

fdef void ev_map_notify(wm_t* wm, xcb_map_notify_event_t* ev){  printf("\x1b[0m%-18s  \x1b[0mwin \x1b[35m%08x  \x1b[0mfocus \x1b[33m%08x  \x1b[0m\n", "XCB_MAP_NOTIFY", ev->window, wm->focus);
  if(ev->window==wm->menu) return;
}

fdef void ev_unmap_notify(wm_t* wm, xcb_unmap_notify_event_t* ev){  printf("\x1b[0m%-18s  \x1b[0mwin \x1b[35m%08x  \x1b[0mfocus \x1b[33m%08x  \x1b[0m\n", "XCB_UNMAP_NOTIFY", ev->window, wm->focus);
  if(ev->window==wm->menu) return;
}

fdef void ev_map_request(wm_t* wm, xcb_map_request_event_t* ev){  printf("\x1b[0m%-18s  \x1b[0mwin \x1b[35m%08x  \x1b[0mfocus \x1b[33m%08x  \x1b[0m\n", "XCB_MAP_REQUEST", ev->window, wm->focus);
  xcb_map_window(wm->connection, ev->window);
  xcb_change_window_attributes(wm->connection, ev->window, XCB_CW_BORDER_PIXEL|XCB_CW_EVENT_MASK, (u32[]){xcb_color(wm->screen,0x00ff00), XCB_EVENT_MASK_KEY_PRESS|XCB_EVENT_MASK_KEY_RELEASE|XCB_EVENT_MASK_FOCUS_CHANGE});
  if(vec_idx(wm->windows, ev->window)==-1)  vec_push(wm->windows, ev->window);
  wm_focus_set(wm, ev->window);  // NOTE! @window MUST be mapped, or @xcb_set_input_focus() generates an XCB error!
  if(xcb_get_pointer_mask(wm->connection,wm->screen->root)!=0x00)  wm_menu_show(wm);  // 4) render

  // u16 pointer_mask = xcb_get_pointer_mask(wm->connection,wm->screen->root);
  // if(wm->focus!=0x00000000 && vec_idx(wm->windows,wm->focus)!=-1)  xcb_configure_window(wm->connection, wm->focus, XCB_CONFIG_WINDOW_BORDER_WIDTH, (u32[]){0});
  // if(pointer_mask!=0x00){  /*xcb_configure_window(wm->connection, ev->window, XCB_CONFIG_WINDOW_BORDER_WIDTH, (u32[]){2});*/  wm_menu_show(wm);  }
  // else                  {  xcb_configure_window(wm->connection, ev->window, XCB_CONFIG_WINDOW_STACK_MODE, (u32[]){XCB_STACK_MODE_ABOVE});  }
  // xcb_set_input_focus(wm->connection, XCB_INPUT_FOCUS_POINTER_ROOT, ev->window, XCB_CURRENT_TIME);  // NOTE! @ev->window MUST be mapped, or @xcb_set_input_focus() generates an XCB error!
  // wm->focus = ev->window;
}

fdef void ev_mapping_notify(wm_t* wm, xcb_mapping_notify_event_t* ev){  // printf("\x1b[92m%-18s  \x1b[0m%d %d  \x1b[0m\n", "XCB_MAPPING_NOTIFY", ev->request, ev->count);
  if(ev->request==XCB_MAPPING_MODIFIER){
    vec_end(wm->modmap);
    wm->modmap = xcb_get_modmap(wm->connection);
  }
}

fdef void ev_loop(wm_t* wm){
  while(wm->running){  // ev loop!
    xcb_generic_event_t* gev = xcb_wait_for_event(wm->connection);  // @xcb_generic_event_t is a polymorphic dstruct! The first 8 bits are an index into a LUT of binary layouts!
    if(gev!=NULL){
      switch(gev->response_type & 0b01111111){
        case 0x00              : ev_error(         wm, (xcb_generic_error_t*)       gev); break;
        case XCB_KEY_PRESS     : ev_key_press(     wm, (xcb_key_press_event_t*)     gev); break;
        case XCB_KEY_RELEASE   : ev_key_release(   wm, (xcb_key_release_event_t*)   gev); break;
        case XCB_FOCUS_IN      : ev_focus_in(      wm, (xcb_focus_in_event_t*)      gev); break;
        case XCB_CREATE_NOTIFY : ev_create_notify( wm, (xcb_create_notify_event_t*) gev); break;
        case XCB_DESTROY_NOTIFY: ev_destroy_notify(wm, (xcb_destroy_notify_event_t*)gev); break;
        case XCB_MAP_NOTIFY    : ev_map_notify(    wm, (xcb_map_notify_event_t*)    gev); break;
        case XCB_UNMAP_NOTIFY  : ev_unmap_notify(  wm, (xcb_unmap_notify_event_t*)  gev); break;
        case XCB_MAP_REQUEST   : ev_map_request(   wm, (xcb_map_request_event_t*)   gev); break;
        case XCB_MAPPING_NOTIFY: ev_mapping_notify(wm, (xcb_mapping_notify_event_t*)gev); break;
      }  // END  switch(gev->response_type & 0b01111111)
      xcb_flush(wm->connection);
      free(gev);  // ALL events must be freed *every time they come*!
    }  // END  if(gev!=NULL)
  }  // END  while(wm->running)
}


// ----------------------------------------------------------------------------------------------------------------------------#
// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk0  mia_main */
#include "miawm_config.h"

fdefe int main(){
  wm_t wm = wm_ini(WM_SHORTCUTS_NDIM_X,WM_SHORTCUTS_NDIM_Y,WM_SHORTCUTS, WM_FONT_NAME,WM_FONT_NDIM_X,WM_FONT_NDIM_Y, WM_MENU_NDIM_X);
  ev_loop(&wm);
  wm_end(&wm);
  exit(0);
}
