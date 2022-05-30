c_ansi_deps = [
  ansi_codes_dep,  
  ansi_utils_dep,  
  term_termpaint_dep,  
]
c_ansi_include_dirs = [
]
c_ansi_lib = library('c_ansi',
  install: false,
  dependencies: c_ansi_deps,
  include_directories: c_ansi_include_dirs,
)
c_ansi_dep = declare_dependency(
  include_directories: c_ansi_include_dirs,
  link_with: c_ansi_lib,
)
