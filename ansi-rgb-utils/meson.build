ansi_rgb_utils_srcs = [
  'ansi-rgb-utils.c',
]
ansi_rgb_utils_deps = [
  ansi_codes_dep,
]

ansi_rgb_utils_lib = static_library('ansi-rgb-utils', 
  install: false, 
  dependencies: ansi_rgb_utils_deps,
  include_directories: [],
)


ansi_rgb_utils_dep = declare_dependency(
  include_directories: [], 
  link_with: ansi_rgb_utils_lib,
)
