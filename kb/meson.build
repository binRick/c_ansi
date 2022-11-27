kb_srcs = [
  'kb.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

kb_include_dirs = [
  '.',
  inc,
]

kb_deps = [
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  module_dep,
  incbin_dep,
  parson_dep,
  tempdir_dep,
  yaml_dep,
  container_of_dep,hash_dep,which_dep,
  libcyaml_dep,
  glib_dep,vips_dep,
]

kb_c_args = [
  '-DINCBIN_SILENCE_BITCODE_WARNING',
]

kb_link_whole = [
  libcyaml_static_lib,
  ]
kb_link_args = [
]

kb_lib = library('kb',
  kb_srcs,
  install: false,
  dependencies: kb_deps,
  c_args: kb_c_args,
  link_whole: kb_link_whole,
  include_directories: kb_include_dirs
)

kb_dep = declare_dependency(
  include_directories: kb_include_dirs,
  link_with: kb_lib,
  link_args: kb_link_args,
)
