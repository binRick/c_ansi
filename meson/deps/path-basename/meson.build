path_basename_lib = static_library('path-basename', 
  '../../../submodules/path-basename.c/src/path-basename.c',
  install: false, 
  dependencies: [
    str_replace_dep,
  ], 
  include_directories: [
    '../../../submodules/path-basename.c/src',
  ]
)
path_basename_dep = declare_dependency(include_directories: ['../../../submodules/path-basename.c/src'], link_with: path_basename_lib)
