opt_srcs = [
  'opt.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

opt_include_dirs = [
  '.',
  inc,
]

opt_deps = [
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
  optparse99_dep,
]

opt_c_args = [
]

opt_link_args = [
]

opt_lib = static_library('opt',
  opt_srcs,
  install: false,
  dependencies: opt_deps,
  c_args: opt_c_args,
  include_directories: opt_include_dirs
)

opt_dep = declare_dependency(
  include_directories: opt_include_dirs,
  link_with: opt_lib,
  link_args: opt_link_args,
)
