#include <stdio.h>
#include <stdlib.h>
#include <wayland-server.h>

#include "compositor.h"

int
main()
{
  int ret = EXIT_FAILURE;
  const char *socket;
  struct wl_display *display;
  struct whs_compositor *compositor;

  display = wl_display_create();
  if (display == NULL) goto out;

  compositor = whs_compositor_create(display);
  if (compositor == NULL) goto out_compositor;

  socket = wl_display_add_socket_auto(display);
  if (socket == NULL) goto out_socket;

  fprintf(stderr, "socket: %s\n", socket);

  wl_display_run(display);

  ret = EXIT_SUCCESS;

out_socket:
  whs_compositor_destroy(compositor);

out_compositor:
  wl_display_destroy(display);

out:
  return ret;
}
