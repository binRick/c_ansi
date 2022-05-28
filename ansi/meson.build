c_ansi_deps = [
  ansi_codes_dep,
  #  ansi_utils_dep,  
  #  ansi_rgb_dep,  
]
c_ansi_lib = library('c-ansi', 
  install: false, 
  dependencies: c_ansi_deps,
  include_directories: [],
)


c_ansi_dep = declare_dependency(
  include_directories: [], 
  link_with: c_ansi_lib,
)  
