/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 2;	/*gap between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int gappih    = 2;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 2;       /* vert inner gap between windows */
static const unsigned int gappoh    = 2;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 2;       /* vert outer gap between windows and screen edge */    
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const char *fonts[]          = { "monospace:size=8" };
static const char dmenufont[]       = " monospace:size=8";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#DAA520";
static const char col_gray4[]       = "#DAA520";
static const char col_cyan[]        = "#006400";
static const char *colors[][3]	    = {
	/*                fg        bg         border */ 

	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel] = { col_gray4, col_cyan, col_cyan  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#006400"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_cyan,  "#006400"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#006400"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_cyan,  "#006400"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#006400"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char *musicplayer[] = { "st", "-e", "ncmpcpp", NULL};


static const Launcher launchers[] = {
       /* command       name to display */
	{ musicplayer,         " " },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *manager[] = { "pcmanfm", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *browser[] = { "chromium", NULL };
static const char *microphone[] = { "mictoggle", NULL };
static const char *gotopcmd[] = { "st", "-e", "gotop", NULL };
static const char *neomutt[] = { "st", "-e", "neomutt", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY, 		        	    XK_F3, 	   spawn,	       SHCMD("pactl set-sink-volume alsa_output.pci-0000_00_1f.3.analog-stereo +2% ") },
	{ MODKEY, 			            XK_F2,     spawn,	       SHCMD("pactl set-sink-volume alsa_output.pci-0000_00_1f.3.analog-stereo -2% ") },
	{ MODKEY, 	            	    XK_F1,     spawn,	       SHCMD("pactl set-sink-mute alsa_output.pci-0000_00_1f.3.analog-stereo toggle") },
	{ MODKEY|ShiftMask,	    	    XK_F3,	   spawn,	       SHCMD("pactl set-sink-volume $(pactl list sinks | awk 'NR==57 {print $2}') ") },	
	{ MODKEY|ShiftMask,	    	    XK_F2, 	   spawn, 	       SHCMD("pactl set-sink-volume $(pactl list sinks | awk 'NR==57 {print $2}') -2% ") },
	{ MODKEY|ShiftMask,	    	    XK_F1,	   spawn,          SHCMD("pactl set-sink-mute $(pactl list sinks | awk 'NR==57 {print $2}') toggle ") },
	{ MODKEY,		        	    XK_Up,	   spawn,          SHCMD("xbacklight -inc 5") },
	{ MODKEY,                       XK_Down,   spawn,          SHCMD("xbacklight -dec 5") },
	{ MODKEY|ShiftMask,		        XK_Left,   spawn, 	       SHCMD("mpc next") },
	{ MODKEY|ShiftMask,	    	    XK_Right,  spawn, 	       SHCMD("mpc prev") },
	{ MODKEY|ShiftMask,	    	    XK_Up,     spawn, 	       SHCMD("mpc volume +2") },
	{ MODKEY|ShiftMask,	    	    XK_Down,   spawn, 	       SHCMD("mpc volume -2") },
	{ MODKEY,                       XK_b,      spawn,          {.v = browser } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_g,      spawn,          {.v = gotopcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,	    	    XK_p, 	   spawn,	       {.v = manager } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = +2 } },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = -2 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = neomutt } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = microphone } },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ 0,				            XK_Menu,   spawn,	       SHCMD("pkill dwmblocks && dwmblocks") },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

