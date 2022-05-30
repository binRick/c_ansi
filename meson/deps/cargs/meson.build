cargs_lib = library('cargs', 
  '../../../submodules/cargs/src/cargs.c',
  install: false, 
  dependencies: [],
  include_directories: [
    '../../../submodules/cargs/include',
  ],
)
cargs_dep = declare_dependency(
  include_directories: [],
  link_with: cargs_lib,
)
