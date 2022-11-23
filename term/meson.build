term_srcs = [
  'term.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

term_include_dirs = [
  '.',
  inc,
]

term_deps = [
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
]

term_c_args = [
]

term_link_args = [
]

term_lib = static_library('term',
  term_srcs,
  install: false,
  dependencies: term_deps,
  c_args: term_c_args,
  include_directories: term_include_dirs
)

term_dep = declare_dependency(
  include_directories: term_include_dirs,
  link_with: term_lib,
  link_args: term_link_args,
)
