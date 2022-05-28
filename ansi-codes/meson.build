ansi_codes_srcs = [
  'ansi-codes.c',
  'ansi-codes.h',
]
ansi_codes_deps = [
]

ansi_codes_lib = library('ansi-codes', 
  install: false, 
  dependencies: ansi_codes_deps,
  include_directories: [],
)


ansi_codes_dep = declare_dependency(
  include_directories: [], 
  link_with: ansi_codes_lib,
)
