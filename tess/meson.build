tess_srcs = [
  'tess.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

tess_include_dirs = [
  '.',
  inc,
]

tess_deps = [
  module_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  tesseract_dep,
]

tess_c_args = [
]

tess_link_args = [
]

tess_lib = static_library('tess',
  tess_srcs,
  install: false,
  dependencies: tess_deps,
  c_args: tess_c_args,
  include_directories: tess_include_dirs
)

tess_dep = declare_dependency(
  include_directories: tess_include_dirs,
  link_with: tess_lib,
  link_args: tess_link_args,
)
