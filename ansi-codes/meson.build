ansi_codes_srcs = [
  'ansi-codes.c',
]
ansi_codes_dirs = [
  '.',
  inc,
]
ansi_codes_deps = [
  module_dep,
  c_vector_dep,
  c_string_buffer_dep,
  c_stringfn_dep,
  vt100utils_dep,
  uuid4_dep,
]

ansi_codes_lib = static_library('ansi-codes', 
  ansi_codes_srcs,
  install: false, 
  dependencies: ansi_codes_deps,
  include_directories: ansi_codes_dirs,
)


ansi_codes_dep = declare_dependency(
  include_directories: ansi_codes_dirs,
  link_with: ansi_codes_lib,
)
