focus_srcs = [
  'focus.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

focus_include_dirs = [
  '.',
  inc,
]

focus_deps = [
  module_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  incbin_dep,
  tempdir_dep,
  which_dep,
  chan_dep,
  c_eventemitter_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  c_focus_dep,
]

focus_c_args = [
]

focus_link_args = [
]

focus_lib = static_library('focus',
  focus_srcs,
  install: false,
  dependencies: focus_deps,
  c_args: focus_c_args,
  include_directories: focus_include_dirs
)

focus_dep = declare_dependency(
  include_directories: focus_include_dirs,
  link_with: focus_lib,
  link_args: focus_link_args,
)
