str_srcs = [
  'str.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

str_include_dirs = [
  '.',
  inc,
]

str_static_libs = [
  ms_lib_static,
  bytes_lib_static,
  timestamp_lib_static,
  log_lib_static,
  c_fsio_lib_static,
  c_stringfn_lib_static,
  c_string_buffer_lib_static,
  #  module_lib_static,
  #c_vector_lib_static,
  ]
str_deps = [
  emojis_dep,
  str_flatten_c_dep,
  str_replace_dep,
  str_truncate_dep,
  occurrences_dep,
  cansid_dep,
  smaz_dep,
  slug_dep,
  chfreq_c_dep,
  uuid4_dep,
  is_number_dep,
  genpassword_c_dep,
  module_dep,
  ansi_codes_dep,
  c_vector_dep,
]

str_c_args = [
]

str_link_args = [
]

str_lib = static_library('str',
  str_srcs,
  install: false,
  dependencies: str_deps,
  link_whole: str_static_libs,
  c_args: str_c_args,
  include_directories: str_include_dirs
)

str_dep = declare_dependency(
  include_directories: str_include_dirs,
  link_with: str_lib,
  link_args: str_link_args,
)
