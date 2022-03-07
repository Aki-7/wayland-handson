#include <wayland-client.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

int running = false;

bool poll(struct wl_display *display)
{
  while (wl_display_prepare_read(display) != 0)
  {
    if (errno != EAGAIN)
      return false;

    if (wl_display_dispatch_pending(display) == -1)
      return false;
  }

  if (wl_display_flush(display) == -1)
    return false;

  if (wl_display_read_events(display) == -1)
    return false;

  if (wl_display_dispatch_pending(display) == -1)
    return false;

  return true;
}

int main(int argc, char const *argv[])
{
  struct wl_display *display;

  if (argc != 2)
  {
    fprintf(stderr, "%s <socket>\n", argv[0]);
    return EXIT_FAILURE;
  }

  display = wl_display_connect(argv[1]);

  running = true;
  while (running) // FIXME: busy loop
  {
    if (poll(display) == false)
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
