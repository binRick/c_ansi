chess_srcs = [
  'chess.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

chess_include_dirs = [
  '.',
  inc,
]

chess_deps = [
  module_dep,
  ansi_codes_dep,
  reproc_dep,
  which_dep,
  str_dep,
  exec_dep,
  subprocess_dep,
  chessterm_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  fen2svg_dep,
  b64_dep,
  incbin_dep,
  vips_dep,
  glib_dep,
  tempdir_dep,
  async_dep,
]

chess_c_args = [
]

chess_link_args = [
]

chess_lib = static_library('chess',
  chess_srcs,
  install: false,
  dependencies: chess_deps,
  c_args: chess_c_args,
  include_directories: chess_include_dirs
)

chess_dep = declare_dependency(
  include_directories: chess_include_dirs,
  link_with: chess_lib,
  link_args: chess_link_args,
)
