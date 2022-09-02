/* appearance */
static const int sloppyfocus        = 1;  /* focus follows mouse */
static const unsigned int borderpx  = 1;  /* border pixel of windows */
static const int lockfullscreen     = 1;  /* 1 will force focus on the fullscreen window */
static const int smartborders       = 1;  /* No borders if there is only one window */
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float bordercolor[]    = {0.5, 0.5, 0.5, 1.0};
static const float focuscolor[]     = {1.0, 0.0, 0.0, 1.0};
static const char cursortheme[]     = NULL; /* theme from /usr/share/cursors/xorg-x11 */
static const unsigned int cursorsize = 24;
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]  = {0.1, 0.1, 0.1, 1.0};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
	{ "firefox",  NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
    .layout = "us,ua",
	.options = "grp:alt_shift_toggle",
};

static const int repeat_rate = 60;
static const int repeat_delay = 180;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE       
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS       
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER 
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* Autostart */
static const char *const autostart[] = {
        "dbus-update-activation-environment", "DISPLAY", "I3SOCK", "SWAYSOCK", "WAYLAND_DISPLAY", "XDG_CURRENT_DESKTOP=sway", NULL,
        "pipewire", NULL,
        "pipewire-pulse", NULL,
        "foot --server", NULL,
        NULL /* terminate */
};

/* If you want to use the windows key change this to WLR_MODIFIER_ALT */
#define MODKEY WLR_MODIFIER_LOGO
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, KEY,            tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,KEY,toggletag,  {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "footclient", NULL };
static const char *menucmd[] = { "fuzzel", "--font=NotoSansMono:size=9", "--no-icons", "--background-color=282828f0", "--text-color=ebdbb2ff", "--selection-color=ebdbb2ff", "--selection-text-color=282828ff", "--border-color=458588ff", "--border-radius=0", "--horizontal-pad=10", "--vertical-pad=10", "--inner-pad=10", "--width=50", NULL };
static const char *backlightup[] = { "light", "-A", "5", NULL };
static const char *backlightdown[] = { "light", "-U", "5", NULL };
static const char *audioraisevolume[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *audiolowervolume[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *audiomicmute[] = { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };
static const char *audiomute[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *micraisevolume[] = { "pactl", "set-source-volume", "@DEFAULT_SOURCE@", "+5%", NULL };
static const char *miclowervolume[] = { "pactl", "set-source-volume", "@DEFAULT_SOURCE@", "-5%", NULL };
static const char *playernext[] = { "playerctl", "next", NULL };
static const char *playerprev[] = { "playerctl", "previous", NULL };
static const char *playerplaypause[] = { "playerctl", "play-pause", NULL };

#include "keys.h"
static const Key keys[] = {
	/* modifier                  key          function        argument */
	{ MODKEY,                    Key_d,       spawn,          {.v = menucmd} },
	{ MODKEY,                    Key_Return,  spawn,          {.v = termcmd} },
	{ MODKEY,                    Key_j,       focusstack,     {.i = +1} },
	{ MODKEY,                    Key_k,       focusstack,     {.i = -1} },
	{ MODKEY,                    Key_i,       incnmaster,     {.i = +1} },
	{ MODKEY,                    Key_d,       incnmaster,     {.i = -1} },
	{ MODKEY,                    Key_h,       setmfact,       {.f = -0.05} },
	{ MODKEY,                    Key_l,       setmfact,       {.f = +0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_Return,  zoom,           {0} },
	{ MODKEY,                    Key_Tab,     view,           {0} },
	{ MODKEY,                    Key_q,       killclient,     {0} },
	{ MODKEY,                    Key_t,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    Key_f,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    Key_m,       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    Key_space,   setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_w,       togglefloating, {0} },
	{ MODKEY,                    Key_f,       togglefullscreen, {0} },
	{ MODKEY,                    Key_0,       view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_0,       tag,            {.ui = ~0} },
	{ MODKEY,                    Key_comma,   focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    Key_period,  focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_comma,   tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_period,  tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(                     Key_1,                       0),
	TAGKEYS(                     Key_2,                       1),
	TAGKEYS(                     Key_3,                       2),
	TAGKEYS(                     Key_4,                       3),
	TAGKEYS(                     Key_5,                       4),
	TAGKEYS(                     Key_6,                       5),
	TAGKEYS(                     Key_7,                       6),
	TAGKEYS(                     Key_8,                       7),
	TAGKEYS(                     Key_9,                       8),
	{ MODKEY|WLR_MODIFIER_SHIFT, Key_q,       quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,Key_BackSpace, quit, {0} },
#define CHVT(KEY,n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, KEY, chvt, {.ui = (n)} }
	CHVT(Key_F1, 1), CHVT(Key_F2,  2),  CHVT(Key_F3,  3),  CHVT(Key_F4,  4),
	CHVT(Key_F5, 5), CHVT(Key_F6,  6),  CHVT(Key_F7,  7),  CHVT(Key_F8,  8),
	CHVT(Key_F9, 9), CHVT(Key_F10, 10), CHVT(Key_F11, 11), CHVT(Key_F12, 12),
    { 0, Key_XF86MonBrightnessUp, spawn, {.v = backlightup } },
    { 0, Key_XF86MonBrightnessDown, spawn, {.v = backlightdown } },
    { 0, Key_XF86AudioRaiseVolume, spawn, {.v = audioraisevolume } },
    { 0, Key_XF86AudioLowerVolume, spawn, {.v = audiolowervolume } },
    { 0, Key_XF86AudioMicMute, spawn, {.v = audiomicmute } },
    { 0, Key_XF86AudioMute, spawn, {.v = audiomute } },
    { WLR_MODIFIER_ALT, Key_XF86AudioRaiseVolume, spawn, {.v = micraisevolume } },
    { WLR_MODIFIER_ALT, Key_XF86AudioLowerVolume, spawn, {.v = miclowervolume } },
    { WLR_MODIFIER_LOGO, Key_XF86AudioRaiseVolume, spawn, {.v = playernext } },
    { WLR_MODIFIER_LOGO, Key_XF86AudioLowerVolume, spawn, {.v = playerprev } },
    { WLR_MODIFIER_LOGO, Key_XF86AudioMute, spawn, {.v = playerplaypause } },
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
