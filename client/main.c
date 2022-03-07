#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>

struct app {
  struct wl_display *display;
  struct wl_compositor *compositor;
};

int running = false;

static bool
poll(struct wl_display *display)
{
  while (wl_display_prepare_read(display) != 0) {
    if (errno != EAGAIN) return false;

    if (wl_display_dispatch_pending(display) == -1) return false;
  }

  if (wl_display_flush(display) == -1) return false;

  if (wl_display_read_events(display) == -1) return false;

  if (wl_display_dispatch_pending(display) == -1) return false;

  return true;
}

static void
global_registry_handler(void *data, struct wl_registry *registry, uint32_t id,
    const char *interface, uint32_t version)
{
  struct app *app = data;
  if (strcmp(interface, "wl_compositor") == 0) {
    app->compositor =
        wl_registry_bind(registry, id, &wl_compositor_interface, version);
  }
}

static void
global_registry_remover(void *data, struct wl_registry *registry, uint32_t id)
{
  (void)data;
  (void)registry;
  (void)id;
}

static const struct wl_registry_listener registry_listener = {
    .global = global_registry_handler,
    .global_remove = global_registry_remover,
};

int
main(int argc, char const *argv[])
{
  struct wl_display *display;
  struct wl_registry *registry;
  struct wl_surface *surface;
  struct app app = {0};

  if (argc != 2) {
    fprintf(stderr, "%s <socket>\n", argv[0]);
    return EXIT_FAILURE;
  }

  display = wl_display_connect(argv[1]);
  app.display = display;

  registry = wl_display_get_registry(display);

  wl_registry_add_listener(registry, &registry_listener, &app);

  wl_display_dispatch(display);
  wl_display_roundtrip(display);

  if (app.compositor == NULL) return EXIT_FAILURE;

  surface = wl_compositor_create_surface(app.compositor);
  (void)surface;

  running = true;

  // FIXME: busy loop
  while (running) {
    if (poll(display) == false) return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
