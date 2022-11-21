/* ewm:- An elegant window manager that just floats perfectly */

#include <X11/Xlib.h>
#include <X11/XF86keysym.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/extensions/shape.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>

#include "ewm.h"
#include "config.h"

static client       *list = {0}, *ws_list[10] = {0}, *cur;
static int          ws = 1, sw, sh, wx, wy, numlock = 0;
static unsigned int ww, wh;
static unsigned int running = 1;
static unsigned int resize_mouse = 0;

static unsigned int scratchtag = 9;  /* last tag reserved for scratchpad */
static unsigned int new_scratch = 0; /* ws of the scratchpad */

static Display      *d;
static XButtonEvent mouse;
static Window       root;

static void (*events[LASTEvent])(XEvent *e) = {
    [ButtonPress]      = button_press,
    [ButtonRelease]    = button_release,
    [ConfigureRequest] = configure_request,
    [KeyPress]         = key_press,
    [MapRequest]       = map_request,
    [MappingNotify]    = mapping_notify,
    [DestroyNotify]    = notify_destroy,
    [EnterNotify]      = notify_enter,
    [MotionNotify]     = notify_motion
};


void win_half(const Arg arg) {
     char m = arg.com[0][0];

     win_size(cur->w, &wx, &wy, &ww, &wh);

     XMoveResizeWindow(d, cur->w, \
        (m == 'w' ? (wx < 0 ? 0 : (unsigned)wx) : m == 'e' ? (wx + ww / 2) : wx < 0 ? 0 : (unsigned)wx),
        (m == 'n' ? (wy < 0 ? 0 : (unsigned)wy) : m == 's' ? (wy + wh / 2) : wy < 0 ? 0 : (unsigned)wy),
        (m == 'w' ? (ww / 2) : m == 'e' ? (ww / 2) : ww),
        (m == 'n' ? (wh / 2) : m == 's' ? (wh / 2) : wh));
}

void win_focus(client *c) {
    cur = c;
    XSetInputFocus(d, cur->w, RevertToParent, CurrentTime);
}

void notify_destroy(XEvent *e) {
    win_del(e->xdestroywindow.window);

    if (list) win_focus(list->prev);
}

void notify_enter(XEvent *e) {
    while(XCheckTypedEvent(d, EnterNotify, e));

    for win if (c->w == e->xcrossing.window) win_focus(c);
}

void notify_motion(XEvent *e) {
    if (!mouse.subwindow || cur->f) return;

    while(XCheckTypedEvent(d, MotionNotify, e));

    int xd = e->xbutton.x_root - mouse.x_root;
    int yd = e->xbutton.y_root - mouse.y_root;

    if (resize_mouse)
        XMoveResizeWindow(d, mouse.subwindow, wx, wy,
            MAX(1, ww + xd), MAX(1, wh + yd));
    else
        XMoveResizeWindow(d, mouse.subwindow,
            wx + ((mouse.button == 1) ? xd : 0),
            wy + ((mouse.button == 1) ? yd : 0),
            MAX(1, ww + ((mouse.button == 3) ? xd : 0)),
            MAX(1, wh + ((mouse.button == 3) ? yd : 0)));

     if (mouse.button == 3 || resize_mouse)
        win_round_corners(mouse.subwindow, ROUND_CORNERS);

}

void key_press(XEvent *e) {
    KeySym keysym = XkbKeycodeToKeysym(d, e->xkey.keycode, 0, 0);

    for (unsigned int i=0; i < sizeof(keys)/sizeof(*keys); ++i) {
        if (keys[i].keysym == keysym &&
            mod_clean(keys[i].mod) == mod_clean(e->xkey.state))
            keys[i].function(keys[i].arg);

        if (keys[i].function == toggle_win_resize_mouse) {
            mouse = e->xbutton;
            win_size(e->xbutton.subwindow, &wx, &wy, &ww, &wh);
        }
    }
}

void button_press(XEvent *e) {
    if (!e->xbutton.subwindow) return;

    win_size(e->xbutton.subwindow, &wx, &wy, &ww, &wh);
    XRaiseWindow(d, e->xbutton.subwindow);
    mouse = e->xbutton;
}

void button_release(XEvent *e) {
    mouse.subwindow = 0;

    if(resize_mouse) {
        resize_mouse = 0;
        XUngrabPointer(d, CurrentTime);
        input_grab(root);
    }
}

void win_add(Window w) {
    client *c;

    if (!(c = (client *) calloc(1, sizeof(client))))
        exit(1);

    c->w = w;

    if (list) {
        list->prev->next = c;
        c->prev          = list->prev;
        list->prev       = c;
        c->next          = list;

    } else {
        list = c;
        list->prev = list->next = list;
    }


    if (new_scratch) {
        c->scratchpad = new_scratch;
        new_scratch = 0;
    }

    ws_save(ws);
}

void win_del(Window w) {
    client *x = 0;

    for win if (c->w == w) x = c;

    if (!list || !x)  return;
    if (x->prev == x) list = 0;
    if (list == x)    list = x->next;
    if (x->next)      x->next->prev = x->prev;
    if (x->prev)      x->prev->next = x->next;

    free(x);
    ws_save(ws);
}

void win_kill(const Arg arg) {
    if (cur) XKillClient(d, cur->w);
}

void win_center(const Arg arg) {
    if (!cur) return;

    win_size(cur->w, &(int){0}, &(int){0}, &ww, &wh);
    XMoveWindow(d, cur->w, (sw - ww) / 2, (sh - wh) / 2);
}

void win_fs(const Arg arg) {
    if (!cur) return;

    if ((cur->f = cur->f ? 0 : 1)) {
        win_size(cur->w, &cur->wx, &cur->wy, &cur->ww, &cur->wh);
        XMoveResizeWindow(d, cur->w, 0, 0, sw, sh);

    } else {
        XMoveResizeWindow(d, cur->w, cur->wx, cur->wy, cur->ww, cur->wh);
    }
  
    win_round_corners(cur->w, cur->f ? 0 : ROUND_CORNERS);
}

void win_round_corners(Window w, int rad) {
    unsigned int ww, wh, dia = 2 * rad;

    win_size(w, &(int){1}, &(int){1}, &ww, &wh);

    if (ww < dia || wh < dia) return;

    Pixmap mask = XCreatePixmap(d, w, ww, wh, 1);

    if (!mask) return;

    XGCValues xgcv;
    GC shape_gc = XCreateGC(d, mask, 0, &xgcv);

    if (!shape_gc) {
        XFreePixmap(d, mask);
        return;
    }

    XSetForeground(d, shape_gc, 0);
    XFillRectangle(d, mask, shape_gc, 0, 0, ww, wh);
    XSetForeground(d, shape_gc, 1);
    XFillArc(d, mask, shape_gc, 0, 0, dia, dia, 0, 23040);
    XFillArc(d, mask, shape_gc, ww-dia-1, 0, dia, dia, 0, 23040);
    XFillArc(d, mask, shape_gc, 0, wh-dia-1, dia, dia, 0, 23040);
    XFillArc(d, mask, shape_gc, ww-dia-1, wh-dia-1, dia, dia, 0, 23040);
    XFillRectangle(d, mask, shape_gc, rad, 0, ww-dia, wh);
    XFillRectangle(d, mask, shape_gc, 0, rad, ww, wh-dia);
    XShapeCombineMask(d, w, ShapeBounding, 0, 0, mask, ShapeSet);
    XFreePixmap(d, mask);
    XFreeGC(d, shape_gc);
}

void win_to_ws(const Arg arg) {
    int tmp = ws;

    if (arg.i == tmp) return;

    new_scratch = cur->scratchpad;

    ws_sel(arg.i);
    win_add(cur->w);
    ws_save(arg.i);

    ws_sel(tmp);
    win_del(cur->w);
    XUnmapWindow(d, cur->w);
    ws_save(tmp);

    if (list) win_focus(list);
}

void win_prev(const Arg arg) {
    if (!cur) return;

    XRaiseWindow(d, cur->prev->w);
    win_focus(cur->prev);
}

void win_next(const Arg arg) {
    if (!cur) return;

    XRaiseWindow(d, cur->next->w);
    win_focus(cur->next);
}

void toggle_win_resize_mouse(const Arg arg) {
    resize_mouse = 1;

    XUngrabKey(d, AnyKey, AnyModifier, root);
    XGrabPointer(d, root, True,
                ButtonPressMask|ButtonReleaseMask|PointerMotionMask,
                GrabModeAsync, GrabModeAsync, None, 0, CurrentTime);
}

void ws_go(const Arg arg) {
    int tmp = ws;

    if (arg.i == ws) return;

    ws_save(ws);
    ws_sel(arg.i);

    for win XMapWindow(d, c->w);

    ws_sel(tmp);

    for win XUnmapWindow(d, c->w);

    ws_sel(arg.i);

    if (list) win_focus(list); else cur = 0;
}

void configure_request(XEvent *e) {
    XConfigureRequestEvent *ev = &e->xconfigurerequest;

    XConfigureWindow(d, ev->window, ev->value_mask, &(XWindowChanges) {
        .x          = ev->x,
        .y          = ev->y,
        .width      = ev->width,
        .height     = ev->height,
        .sibling    = ev->above,
        .stack_mode = ev->detail
    });

    win_round_corners(ev->window, ROUND_CORNERS);
}

void map_request(XEvent *e) {
    Window w = e->xmaprequest.window;

    XSelectInput(d, w, StructureNotifyMask|EnterWindowMask);
    win_size(w, &wx, &wy, &ww, &wh);
    win_add(w);
    cur = list->prev;

    if (wx + wy == 0) win_center((Arg){0});

    win_round_corners(w, ROUND_CORNERS);
    XMapWindow(d, w);
    win_focus(list->prev);
}

void mapping_notify(XEvent *e) {
    XMappingEvent *ev = &e->xmapping;

    if (ev->request == MappingKeyboard || ev->request == MappingModifier) {
        XRefreshKeyboardMapping(ev);
        input_grab(root);
    }
}

void run(const Arg arg) {
    if (fork()) return;
    if (d) close(ConnectionNumber(d));

    setsid();
    execvp((char*)arg.com[0], (char**)arg.com);
}

void input_grab(Window root) {
    unsigned int i, j, modifiers[] = {0, LockMask, numlock, numlock|LockMask};
    XModifierKeymap *modmap = XGetModifierMapping(d);
    KeyCode code;

    for (i = 0; i < 8; i++)
        for (int k = 0; k < modmap->max_keypermod; k++)
            if (modmap->modifiermap[i * modmap->max_keypermod + k]
                == XKeysymToKeycode(d, 0xff7f))
                numlock = (1 << i);

    XUngrabKey(d, AnyKey, AnyModifier, root);

    for (i = 0; i < sizeof(keys)/sizeof(*keys); i++)
        if ((code = XKeysymToKeycode(d, keys[i].keysym)))
            for (j = 0; j < sizeof(modifiers)/sizeof(*modifiers); j++)
                XGrabKey(d, code, keys[i].mod | modifiers[j], root,
                        True, GrabModeAsync, GrabModeAsync);

    for (i = 1; i < 4; i += 2)
        for (j = 0; j < sizeof(modifiers)/sizeof(*modifiers); j++)
            XGrabButton(d, i, MOD | modifiers[j], root, True,
                ButtonPressMask|ButtonReleaseMask|PointerMotionMask,
                GrabModeAsync, GrabModeAsync, 0, 0);

    XFreeModifiermap(modmap);
}

void scratchpad_toggle(const Arg arg) {
   // int clients_c = 0;
    client *scratch_found = NULL;

    for (long unsigned int i = 1; i < LEN(ws_list); i++) {
        client *c = ws_list[i];
        if (c == NULL)
            continue;

        Window w_temp = c->w;
        int is_first = 1;

        for (;is_first != (c->w != w_temp); is_first = 0, c = c->next) {
            if (c->scratchpad) {
                scratch_found = c;
                break;
            }
        }

        if (scratch_found)
            break;
    }

    // Scratchpad not found.

    if (!scratch_found) {
        new_scratch = ws;
        run(arg);
        return;
    }

    // Scratchpad is on current workspace. So let's hide it.

    if (scratch_found->scratchpad == ws) {
        int temp_ws = ws;

        ws_sel(scratchtag);
        new_scratch = scratchtag;
        win_add(scratch_found->w);
        ws_save(scratchtag);

        ws_sel(temp_ws);
        win_del(scratch_found->w);
        ws_save(temp_ws);

        XUnmapWindow(d, scratch_found->w);
        if (list) win_focus(list); else cur = 0;

        return;
    }

    // Moving scratchpad to current workspace.

    int temp_ws = ws;

    ws_sel(scratch_found->scratchpad);
    win_del(scratch_found->w);
    ws_save(scratch_found->scratchpad);

    ws_sel(temp_ws);
    new_scratch = temp_ws;
    win_add(scratch_found->w);
    ws_save(temp_ws);

    XMapWindow(d, scratch_found->w);
    win_focus(scratch_found);
    XRaiseWindow(d, scratch_found->w);
}

void wm_quit(const Arg arg) {
    running = 0;
}

int main(void) {
    XEvent ev;

    if (!(d = XOpenDisplay(0))) exit(1);

    signal(SIGCHLD, SIG_IGN);
    XSetErrorHandler(xerror);

    int s = DefaultScreen(d);
    root  = RootWindow(d, s);
    sw    = XDisplayWidth(d, s);
    sh    = XDisplayHeight(d, s);

    XSelectInput(d,  root, SubstructureRedirectMask);
    XDefineCursor(d, root, XCreateFontCursor(d, 68));
    input_grab(root);

    while (running && !XNextEvent(d, &ev))
        if (events[ev.type]) events[ev.type](&ev);

    XCloseDisplay(d);
}
