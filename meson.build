project(
  'wayland-handson', 'c',
  version: '0.0.1',
  license: 'Apache-2.0',
  meson_version: '>= 0.52.1',
  default_options:  [ 'warning_level=3', 'werror=true', 'optimization=2', 'c_std=gnu11' ],
)

# dependencies

dep_wayland_sever = dependency('wayland-server')
dep_wayland_client = dependency('wayland-client')
dep_wayland_scanner = dependency('wayland-scanner', version: '>= 1.14.91')

subdir('server')
subdir('client')
