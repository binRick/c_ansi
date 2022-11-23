ansi_rgb_utils_srcs = [
  'ansi-rgb-utils.c',
]
ansi_rgb_utils_incs = [
  inc,
]
ansi_rgb_utils_deps = [
  ansi_codes_dep,
  hsluv_c_dep,
  rgba_dep,
  ansi_utils_dep,
  c_string_buffer_dep,log_dep,
  c_stringfn_dep,
]

ansi_rgb_utils_lib = library('ansi-rgb-utils', 
  ansi_rgb_utils_srcs,
  install: false, 
  dependencies: ansi_rgb_utils_deps,
  include_directories: ansi_rgb_utils_incs,
)


ansi_rgb_utils_dep = declare_dependency(
  include_directories: ansi_rgb_utils_incs,
  link_with: ansi_rgb_utils_lib,
)
