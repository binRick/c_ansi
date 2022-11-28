qr_srcs = [
  'qr.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

qr_include_dirs = [
  '.',
  inc,
]

qr_deps = [
  module_dep,
  libqrencode_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  qrcode_dep,
]

qr_c_args = [
]

qr_link_args = [
]

qr_lib = static_library('qr',
  qr_srcs,
  install: false,
  dependencies: qr_deps,
  c_args: qr_c_args,
  include_directories: qr_include_dirs
)

qr_dep = declare_dependency(
  include_directories: qr_include_dirs,
  link_with: qr_lib,
  link_args: qr_link_args,
)
