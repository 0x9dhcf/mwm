/*
 * Copyright (c) 2019 Pierre Evenou
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

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <xcb/xcb.h>
#include <xcb/xcb_icccm.h>
#include <xcb/xcb_ewmh.h>

#include "rectangle.h"

typedef struct _Monitor Monitor;

typedef enum _Mode {
    MODE_ANY,
    MODE_TILED,
    MODE_FLOATING,
    MODE_FULLSCREEN
} Mode;

typedef int State;

#define STATE_ANY           0x00
#define STATE_ACCEPT_FOCUS  0x01
#define STATE_STICKY        0x02
#define STATE_URGENT        0x04

typedef struct _Strut {
    int top;
    int bottom;
    int left;
    int right;
} Strut;

typedef struct _SizeHints {
    int     base_width;
    int     base_height;
    int     width_increment;
    int     height_increment;
    int     min_width;
    int     min_height;
    int     max_width;
    int     max_height;
    double  min_aspect_ratio;
    double  max_aspect_ratio;
} SizeHints;

typedef struct _Client {
    xcb_window_t    window;
    Mode            mode;
    Mode            saved_mode;
    char            instance[256];
    char            class[256];
    Rectangle       tiling_geometry;
    Rectangle       floating_geometry;
    int             border_width;
    int             border_color;
    State           state;
    Strut           strut;
    SizeHints       size_hints;
    xcb_window_t    transient;
    Monitor         *monitor;
    int             tagset;
    int             saved_tagset;
    struct _Client  *prev;
    struct _Client  *next;
} Client;

void client_initialize(Client *c, xcb_window_t w);
void client_set_floating(Client *c, Rectangle *r);
void client_set_tiling(Client *c, Rectangle *r);
void client_set_mode(Client *c, Mode m);
void client_set_tagset(Client *c, int tagset);
void client_set_sticky(Client *c, int sticky);
void client_set_fullscreen(Client *c, int fullscreen);
void client_set_urgent(Client *c, int urgency);
void client_set_input_focus(Client *c);
void client_receive_focus(Client *c);
void client_loose_focus(Client *c);
void client_hide(Client *c);
void client_show(Client *c);
void client_apply_size_hints(Client *c);
void client_notify(Client *c);
int client_is_visible(Client *c);
int client_update_strut(Client *c);
int client_update_size_hints(Client *c);
int client_update_wm_hints(Client *c);
int client_update_window_type(Client *c);
// Move to monitor
Client *client_next(Client *client, Mode mode, State state);
Client *client_previous(Client *client, Mode mode, State state);

#endif
