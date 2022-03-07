#include "compositor.h"

#include <stdio.h>
#include <stdlib.h>
#include <wayland-server.h>

static void
whs_compositor_protocol_create_surface(
    struct wl_client *client, struct wl_resource *resource, uint32_t id)
{
  (void)client;
  (void)resource;
  (void)id;
  fprintf(stderr, "CREATE SURFACE!!!");
}

static void
whs_compositor_protocol_create_region(
    struct wl_client *client, struct wl_resource *resource, uint32_t id)
{
  (void)client;
  (void)resource;
  (void)id;
}

static const struct wl_compositor_interface compositor_interface = {
    .create_surface = whs_compositor_protocol_create_surface,
    .create_region = whs_compositor_protocol_create_region,
};

static void
bind(struct wl_client *client, void *data, uint32_t version, uint32_t id)
{
  struct whs_compositor *compositor = data;
  struct wl_resource *resource;

  resource = wl_resource_create(client, &wl_compositor_interface, version, id);
  if (resource == NULL) {
    wl_client_post_no_memory(client);
    return;
  }

  wl_resource_set_implementation(
      resource, &compositor_interface, compositor, NULL);
}

WL_EXPORT struct whs_compositor *
whs_compositor_create(struct wl_display *display)
{
  struct whs_compositor *compositor;
  struct wl_global *global;

  compositor = calloc(1, sizeof *compositor);
  if (compositor == NULL) goto err;

  global =
      wl_global_create(display, &wl_compositor_interface, 4, compositor, bind);

  compositor->global = global;

  return compositor;

err:
  return NULL;
}

WL_EXPORT void
whs_compositor_destroy(struct whs_compositor *compositor)
{
  wl_global_destroy(compositor->global);
  free(compositor);
}
