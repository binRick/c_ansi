jinja2_cli_srcs = [
  'jinja2-cli.c',
]
jinja2_cli_dirs = [
  '.',
  '../../',
  '../',
  inc,
]
jinja2_cli_deps = [
  subprocess_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  c_fsio_dep,
  timestamp_dep,
  which_dep,
]

jinja2_cli_lib = static_library('jinja2-cli', 
  jinja2_cli_srcs,
  install: false, 
  dependencies: jinja2_cli_deps,
  include_directories: jinja2_cli_dirs,
)


jinja2_cli_dep = declare_dependency(
  include_directories: jinja2_cli_dirs,
  link_with: jinja2_cli_lib,
)
