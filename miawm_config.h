// ----------------------------------------------------------------------------------------------------------------------------#
#if 1  // keyboard layout (in x11 keycodes): QGMLWB
#define WM_KEY_00  0x18  // {h:l x:0 y:0}
#define WM_KEY_10  0x2a  // {h:l x:1 y:0}
#define WM_KEY_20  0x3a  // {h:l x:2 y:0}
#define WM_KEY_30  0x2e  // {h:l x:3 y:0}
#define WM_KEY_40  0x19  // {h:l x:4 y:0}
#define WM_KEY_01  0x28  // {h:l x:0 y:1}
#define WM_KEY_11  0x27  // {h:l x:1 y:1}
#define WM_KEY_21  0x1c  // {h:l x:2 y:1}
#define WM_KEY_31  0x39  // {h:l x:3 y:1}
#define WM_KEY_41  0x1b  // {h:l x:4 y:1}
#define WM_KEY_02  0x34  // {h:l x:0 y:2}
#define WM_KEY_12  0x35  // {h:l x:1 y:2}
#define WM_KEY_22  0x36  // {h:l x:2 y:2}
#define WM_KEY_32  0x29  // {h:l x:3 y:2}
#define WM_KEY_42  0x2c  // {h:l x:4 y:2}
#define WM_KEY_50  0x38  // {h:r x:5 y:0}
#define WM_KEY_60  0x1d  // {h:r x:6 y:0}
#define WM_KEY_70  0x1e  // {h:r x:7 y:0}
#define WM_KEY_80  0x37  // {h:r x:8 y:0}
#define WM_KEY_90  0x30  // {h:r x:9 y:0}
#define WM_KEY_51  0x1f  // {h:r x:5 y:1}
#define WM_KEY_61  0x26  // {h:r x:6 y:1}
#define WM_KEY_71  0x1a  // {h:r x:7 y:1}
#define WM_KEY_81  0x20  // {h:r x:8 y:1}
#define WM_KEY_91  0x2b  // {h:r x:9 y:1}
#define WM_KEY_52  0x2d  // {h:r x:5 y:2}
#define WM_KEY_62  0x21  // {h:r x:6 y:2}
#define WM_KEY_72  0x3b  // {h:r x:7 y:2}
#define WM_KEY_82  0x3c  // {h:r x:8 y:2}
#define WM_KEY_92  0x3d  // {h:r x:9 y:2}
#endif

#if 0  // keyboard layout (in x11 keycodes): QWERTY  // TODO!
#define WM_KEY_00  0x??  // {h:l x:0 y:0}
#define WM_KEY_10  0x??  // {h:l x:1 y:0}
#define WM_KEY_20  0x??  // {h:l x:2 y:0}
#define WM_KEY_30  0x??  // {h:l x:3 y:0}
#define WM_KEY_40  0x??  // {h:l x:4 y:0}
#define WM_KEY_01  0x??  // {h:l x:0 y:1}
#define WM_KEY_11  0x??  // {h:l x:1 y:1}
#define WM_KEY_21  0x??  // {h:l x:2 y:1}
#define WM_KEY_31  0x??  // {h:l x:3 y:1}
#define WM_KEY_41  0x??  // {h:l x:4 y:1}
#define WM_KEY_02  0x??  // {h:l x:0 y:2}
#define WM_KEY_12  0x??  // {h:l x:1 y:2}
#define WM_KEY_22  0x??  // {h:l x:2 y:2}
#define WM_KEY_32  0x??  // {h:l x:3 y:2}
#define WM_KEY_42  0x??  // {h:l x:4 y:2}
#define WM_KEY_50  0x??  // {h:r x:5 y:0}
#define WM_KEY_60  0x??  // {h:r x:6 y:0}
#define WM_KEY_70  0x??  // {h:r x:7 y:0}
#define WM_KEY_80  0x??  // {h:r x:8 y:0}
#define WM_KEY_90  0x??  // {h:r x:9 y:0}
#define WM_KEY_51  0x??  // {h:r x:5 y:1}
#define WM_KEY_61  0x??  // {h:r x:6 y:1}
#define WM_KEY_71  0x??  // {h:r x:7 y:1}
#define WM_KEY_81  0x??  // {h:r x:8 y:1}
#define WM_KEY_91  0x??  // {h:r x:9 y:1}
#define WM_KEY_52  0x??  // {h:r x:5 y:2}
#define WM_KEY_62  0x??  // {h:r x:6 y:2}
#define WM_KEY_72  0x??  // {h:r x:7 y:2}
#define WM_KEY_82  0x??  // {h:r x:8 y:2}
#define WM_KEY_92  0x??  // {h:r x:9 y:2}
#endif

// ----------------------------------------------------------------------------------------------------------------------------#
/* keyboard shortcuts: a 2-array of function pointers!
  x: x11 modifier MASK (NOT modifier keycode)! run `xmodmap -pm`  // NOTE! Modifier masks must be valid X11/XCB modifier masks, because @xcb_grab_key() only accepts valid X11/XCB modifier masks... You can assign map keycodes to modifiers in `~/.Xmodmap` or w/ @XSetModifierMapping(). X11 is hardcoded to only support 8 modifiers (yuck!)
  y: x11 keycode!                              run `xmodmap -pke`
*/
void (*WM_SHORTCUTS[WM_SHORTCUTS_NDIM_X][WM_SHORTCUTS_NDIM_Y])(wm_t*) = {  // keyboard shortcuts!
  // ----------------------------------------------------------------
  /*{h:? x:? y:?}*/ [0x00][0x6b] = cmd_exec_ss,  // print screen!
  // ----------------------------------------------------------------
  /*{h:l x:0 y:0}*/ [XCB_MOD_MASK_4][WM_KEY_00] = cmd_exec_alsamixer,
  /*{h:l x:1 y:0}*/ // [XCB_MOD_MASK_4][WM_KEY_10] = cmd_noop,
  /*{h:l x:2 y:0}*/ // [XCB_MOD_MASK_4][WM_KEY_20] = cmd_noop,
  /*{h:l x:3 y:0}*/ // [XCB_MOD_MASK_4][WM_KEY_30] = cmd_noop,
  /*{h:l x:4 y:0}*/ // [XCB_MOD_MASK_4][WM_KEY_40] = cmd_noop,
  /*{h:l x:0 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_01] = cmd_exec_nav,
  /*{h:l x:1 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_11] = cmd_exec_web,
  /*{h:l x:2 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_21] = cmd_exec_txt,
  /*{h:l x:3 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_31] = cmd_exec_term,
  /*{h:l x:4 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_41] = cmd_exec_mon,
  /*{h:l x:0 y:2}*/ // [XCB_MOD_MASK_4][WM_KEY_02] = cmd_noop,
  /*{h:l x:1 y:2}*/ // [XCB_MOD_MASK_4][WM_KEY_12] = cmd_noop,
  /*{h:l x:2 y:2}*/ [XCB_MOD_MASK_4][WM_KEY_22] = cmd_focus_close,
  /*{h:l x:3 y:2}*/ [XCB_MOD_MASK_4][WM_KEY_32] = cmd_focus_kill2,
  /*{h:l x:4 y:2}*/ [XCB_MOD_MASK_4][WM_KEY_42] = cmd_focus_kill9,
  /*{h:r x:5 y:0}*/ [XCB_MOD_MASK_4][WM_KEY_50] = cmd_focus_prev,
  /*{h:r x:6 y:0}*/ [XCB_MOD_MASK_4][WM_KEY_60] = cmd_focus_grid_00_22,
  /*{h:r x:7 y:0}*/ [XCB_MOD_MASK_4][WM_KEY_70] = cmd_focus_grid_10_22,
  /*{h:r x:8 y:0}*/ [XCB_MOD_MASK_4][WM_KEY_80] = cmd_focus_grid_00_21,
  /*{h:r x:9 y:0}*/ [XCB_MOD_MASK_4][WM_KEY_90] = cmd_focus_grid_00_11,
  /*{h:r x:5 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_51] = cmd_focus_next,
  /*{h:r x:6 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_61] = cmd_focus_grid_01_22,
  /*{h:r x:7 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_71] = cmd_focus_grid_11_22,
  /*{h:r x:8 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_81] = cmd_focus_grid_10_21,
  /*{h:r x:9 y:1}*/ [XCB_MOD_MASK_4][WM_KEY_91] = cmd_focus_hide,
  /*{h:r x:5 y:2}*/ // [XCB_MOD_MASK_4][WM_KEY_52] = cmd_noop,
  /*{h:r x:6 y:2}*/ // [XCB_MOD_MASK_4][WM_KEY_62] = cmd_noop,
  /*{h:r x:7 y:2}*/ // [XCB_MOD_MASK_4][WM_KEY_72] = cmd_noop,
  /*{h:r x:8 y:2}*/ // [XCB_MOD_MASK_4][WM_KEY_82] = cmd_noop,
  /*{h:r x:9 y:2}*/ // [XCB_MOD_MASK_4][WM_KEY_92] = cmd_noop,
  // ----------------------------------------------------------------
  /*{h:l x:0 y:0}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_00] = cmd_noop,
  /*{h:l x:1 y:0}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_10] = cmd_noop,
  /*{h:l x:2 y:0}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_20] = cmd_noop,
  /*{h:l x:3 y:0}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_30] = cmd_noop,
  /*{h:l x:4 y:0}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_40] = cmd_noop,
  /*{h:l x:0 y:1}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_01] = cmd_noop,
  /*{h:l x:1 y:1}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_11] = cmd_noop,
  /*{h:l x:2 y:1}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_21] = cmd_noop,
  /*{h:l x:3 y:1}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_31] = cmd_noop,
  /*{h:l x:4 y:1}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_41] = cmd_noop,
  /*{h:l x:0 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_02] = cmd_noop,
  /*{h:l x:1 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_12] = cmd_noop,
  /*{h:l x:2 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_22] = cmd_noop,
  /*{h:l x:3 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_32] = cmd_noop,
  /*{h:l x:4 y:2}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_42] = cmd_exit,
  /*{h:r x:5 y:0}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_50] = cmd_noop,
  /*{h:r x:6 y:0}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_60] = cmd_focus_grid_00_44,
  /*{h:r x:7 y:0}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_70] = cmd_focus_grid_10_44,
  /*{h:r x:8 y:0}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_80] = cmd_focus_grid_20_44,
  /*{h:r x:9 y:0}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_90] = cmd_focus_grid_30_44,
  /*{h:r x:5 y:1}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_51] = cmd_noop,
  /*{h:r x:6 y:1}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_61] = cmd_focus_grid_01_44,
  /*{h:r x:7 y:1}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_71] = cmd_focus_grid_11_44,
  /*{h:r x:8 y:1}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_81] = cmd_focus_grid_21_44,
  /*{h:r x:9 y:1}*/ [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_91] = cmd_focus_grid_31_44,
  /*{h:r x:5 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_52] = cmd_noop,
  /*{h:r x:6 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_62] = cmd_noop,
  /*{h:r x:7 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_72] = cmd_noop,
  /*{h:r x:8 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_82] = cmd_noop,
  /*{h:r x:9 y:2}*/ // [XCB_MOD_MASK_4|XCB_MOD_MASK_2][WM_KEY_82] = cmd_noop,
  // ----------------------------------------------------------------
  /*{h:l x:0 y:0}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_00] = cmd_noop,
  /*{h:l x:1 y:0}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_10] = cmd_noop,
  /*{h:l x:2 y:0}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_20] = cmd_noop,
  /*{h:l x:3 y:0}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_30] = cmd_noop,
  /*{h:l x:4 y:0}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_40] = cmd_noop,
  /*{h:l x:0 y:1}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_01] = cmd_noop,
  /*{h:l x:1 y:1}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_11] = cmd_noop,
  /*{h:l x:2 y:1}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_21] = cmd_noop,
  /*{h:l x:3 y:1}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_31] = cmd_noop,
  /*{h:l x:4 y:1}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_41] = cmd_noop,
  /*{h:l x:0 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_02] = cmd_noop,
  /*{h:l x:1 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_12] = cmd_noop,
  /*{h:l x:2 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_22] = cmd_noop,
  /*{h:l x:3 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_32] = cmd_noop,
  /*{h:l x:4 y:2}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_42] = cmd_exit,
  /*{h:r x:5 y:0}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_50] = cmd_noop,
  /*{h:r x:6 y:0}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_60] = cmd_focus_grid_02_44,
  /*{h:r x:7 y:0}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_70] = cmd_focus_grid_12_44,
  /*{h:r x:8 y:0}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_80] = cmd_focus_grid_22_44,
  /*{h:r x:9 y:0}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_90] = cmd_focus_grid_32_44,
  /*{h:r x:5 y:1}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_51] = cmd_noop,
  /*{h:r x:6 y:1}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_61] = cmd_focus_grid_03_44,
  /*{h:r x:7 y:1}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_71] = cmd_focus_grid_13_44,
  /*{h:r x:8 y:1}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_81] = cmd_focus_grid_23_44,
  /*{h:r x:9 y:1}*/ [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_91] = cmd_focus_grid_33_44,
  /*{h:r x:5 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_52] = cmd_noop,
  /*{h:r x:6 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_62] = cmd_noop,
  /*{h:r x:7 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_72] = cmd_noop,
  /*{h:r x:8 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_82] = cmd_noop,
  /*{h:r x:9 y:2}*/ // [XCB_MOD_MASK_1|XCB_MOD_MASK_2][WM_KEY_82] = cmd_noop,
};

// ----------------------------------------------------------------------------------------------------------------------------#
#define WM_FONT_NAME    "-schumacher-clean-medium-r-normal--6-60-75-75-c-50-iso646.1991-irv"
#define WM_FONT_NDIM_X  5
#define WM_FONT_NDIM_Y  6

#define WM_MENU_NDIM_X  0x380  // in pixels!
