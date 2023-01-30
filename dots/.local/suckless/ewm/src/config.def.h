#ifndef CONFIG_H
#define CONFIG_H
#define MOD Mod4Mask
#define ROUND_CORNERS 10

const char* menu[]    = {"dmenu_run",           0};
const char* term[]    = {"st",                  0};
const char* ss[]      = {"swpb",     "-b",     0};
const char* ssel[]    = {"swpb",     "-s",     0};
const char* pmenu[]   = {"swpb",     "-p",     0};
const char* wsearch[] = {"swpb",     "-w",     0};
const char* briup[]   = {"brillo", "-A", "3",    0};
const char* bridown[] = {"brillo", "-U", "3",    0};
const char* voldown[] = {"pactl", "set-sink-volume", "0", "-5%",         NULL};
const char* volup[]   = {"pactl", "set-sink-volume", "0", "+5%",         NULL};
const char* volmute[] = {"pactl", "set-sink-mute",   "0", "toggle",      NULL};
const char* scratch[] = {"st", 0};

static struct key keys[] = {
   
    {MOD,           XK_c,   win_kill,   {0}},
    {MOD,           XK_x,   win_center, {0}},
    {MOD,           XK_f,   win_fs,     {0}},
    {MOD|ShiftMask, XK_q,   wm_quit,    {0}},
    {MOD,           XK_r,   toggle_win_resize_mouse,   {0}},

    {Mod1Mask,           XK_Tab, win_next,   {0}},
    {Mod1Mask|ShiftMask, XK_Tab, win_prev,   {0}},

    {MOD,           XK_space,  run,  {.com = menu}},
    {MOD,           XK_p,      run,  {.com = ss}},
    {MOD|ShiftMask, XK_p,      run,  {.com = ssel}},
    {MOD|ShiftMask, XK_x,      run,  {.com = pmenu}},
    {MOD,           XK_w,      run,  {.com = wsearch}},
    {MOD,           XK_Return, run,  {.com = term}},
    {MOD,           XK_grave,  scratchpad_toggle,  {.com = scratch}},

    {0,   XF86XK_AudioLowerVolume,  run, {.com = voldown}},
    {0,   XF86XK_AudioRaiseVolume,  run, {.com = volup}},
    {0,   XF86XK_AudioMute,         run, {.com = volmute}},
    {0,   XF86XK_MonBrightnessUp,   run, {.com = briup}},
    {0,   XF86XK_MonBrightnessDown, run, {.com = bridown}},

    {MOD|Mod1Mask,  XK_k,  win_half,  {.com = (const char*[]){"n"}}},
    {MOD|Mod1Mask,  XK_j,  win_half,  {.com = (const char*[]){"s"}}},
    {MOD|Mod1Mask,  XK_l,  win_half,  {.com = (const char*[]){"e"}}},
    {MOD|Mod1Mask,  XK_h,  win_half,  {.com = (const char*[]){"w"}}},

    {MOD,           XK_1, ws_go,     {.i = 1}},
    {MOD|ShiftMask, XK_1, win_to_ws, {.i = 1}},
    {MOD,           XK_2, ws_go,     {.i = 2}},
    {MOD|ShiftMask, XK_2, win_to_ws, {.i = 2}},
    {MOD,           XK_3, ws_go,     {.i = 3}},
    {MOD|ShiftMask, XK_3, win_to_ws, {.i = 3}},
    {MOD,           XK_4, ws_go,     {.i = 4}},
    {MOD|ShiftMask, XK_4, win_to_ws, {.i = 4}},
    {MOD,           XK_5, ws_go,     {.i = 5}},
    {MOD|ShiftMask, XK_5, win_to_ws, {.i = 5}},
    {MOD,           XK_6, ws_go,     {.i = 6}},
    {MOD|ShiftMask, XK_6, win_to_ws, {.i = 6}},
};
#endif
