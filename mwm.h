/*
 * Copyright (c) 2019, 2020 Pierre Evenou
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __MWM_H__
#define __MWM_H__

#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xkb.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-compose.h>
#include <xkbcommon/xkbcommon-x11.h>

#include "monitor.h"
#include "client.h"

#ifndef VERSION
#define VERSION "0.0"
#endif

#define WMNAME "mwm"

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

/* atoms */
enum {
    WM_TAKE_FOCUS,
    MWM_MONITOR_TAGS,
    MWM_MONITOR_TAGSET,
    MWM_FOCUSED,
    MWM_FOCUSED_TAGSET,
    MWM_ATOM_COUNT
};

typedef enum _Direction {
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT
} Direction;

/* xcb context */
xcb_connection_t       *g_xcb;
int                     g_screen_id;
xcb_screen_t           *g_screen;
xcb_window_t            g_root;
xcb_visualtype_t       *g_visual;
xcb_ewmh_connection_t   g_ewmh;
xcb_atom_t              g_atoms[MWM_ATOM_COUNT];
struct xkb_state       *g_xkb_state;

/* globals */
void quit();
void dump();
void toggle_bar();
void refresh_bar();

/* monitors */
void scan_monitors();

/* windows */
void manage(xcb_window_t window);
Client * lookup(xcb_window_t window);
void forget(xcb_window_t window);
void focus(Client *client);
void unfocus(Client *client);

/* focus */
void focus_next_client();
void focus_previous_client();
void focus_next_monitor();
void focus_previous_monitor();
void focus_clicked_monitor(int x, int y);

/* focused monitor */ 
void focused_monitor_update_main_views(int by);
void focused_monitor_set_layout(Layout layout);
void focused_monitor_rotate_clockwise();
void focused_monitor_rotate_counter_clockwise();
void focused_monitor_set_tag(int tag);
void focused_monitor_toggle_tag(int tag);

/* focused client */
void focused_client_kill();
void focused_client_toggle_mode();
void focused_client_move(Direction direction);
void focused_client_to_next_monitor();
void focused_client_to_previous_monitor();
void focused_client_resize(int width, int height);
void focused_client_set_tag(int tag);
void focused_client_toggle_tag(int tag);

#endif
