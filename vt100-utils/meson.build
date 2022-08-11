vt100_utils_srcs = [
  'vt100-utils.c',
  'vt100-utils-libterminput.c',
]
vt100_utils_include_dirs = [
  '.',
  inc,
]

vt100_utils_deps = [
  module_dep,
  c_vector_dep,
  c_string_buffer_dep,
  libterminput_dep,
  c_stringfn_dep,
  vt100utils_dep,
  uuid4_dep,  
  ansi_codes_dep,
  wildcardcmp_dep,
  ansi_utils_dep,
]

vt100_utils_lib = static_library('vt100-utils',
  vt100_utils_srcs,
  install: false,
  dependencies: vt100_utils_deps,
  include_directories: vt100_utils_include_dirs,
)

vt100_utils_dep = declare_dependency(
  include_directories: vt100_utils_include_dirs,
  link_with: vt100_utils_lib,
)
