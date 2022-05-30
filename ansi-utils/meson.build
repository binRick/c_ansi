ansi_utils_srcs = [
  'ansi-utils.c',
]
ansi_utils_deps = [
  ansi_codes_dep,
]


ansi_utils_lib = library('ansi-utils', 
  install: false, 
  dependencies: ansi_utils_deps,
  include_directories: [],
)


ansi_utils_dep = declare_dependency(
  include_directories: [], 
  link_with: ansi_utils_lib,
)
