ansi_utils_srcs = [
  'ansi-utils.c',
]
ansi_utils_incs = [
  inc,
  '../',
]
ansi_utils_deps = [
  ansi_codes_dep,
  b64_dep,
]


ansi_utils_lib = static_library('ansi-utils', 
  ansi_utils_srcs,
  install: false, 
  dependencies: ansi_utils_deps,
  include_directories: ansi_utils_incs,
)


ansi_utils_dep = declare_dependency(
  include_directories: ansi_utils_incs,
  link_with: ansi_utils_lib,
)
