#ifndef WAYLAND_HANDSON_SERVER_COMPOSITOR_H
#define WAYLAND_HANDSON_SERVER_COMPOSITOR_H

#include <wayland-server.h>

struct whs_compositor {
  struct wl_global *global;
};

struct whs_compositor *whs_compositor_create(struct wl_display *display);

void whs_compositor_destroy(struct whs_compositor *compositor);

#endif  //  WAYLAND_HANDSON_SERVER_COMPOSITOR_H
