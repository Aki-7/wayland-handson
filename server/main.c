#include <wayland-server.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
  int ret = EXIT_FAILURE;
  const char *socket;
  struct wl_display *display;

  display = wl_display_create();
  if (display == NULL)
    goto out;

  socket = wl_display_add_socket_auto(display);
  if (socket == NULL)
    goto out_socket;

  fprintf(stderr, "socket: %s\n", socket);

  wl_display_run(display);

  ret = EXIT_SUCCESS;

out_socket:
  wl_display_destroy(display);

out:
  return ret;
}
