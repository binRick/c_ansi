c_fsio_lib = library('c_fsio', 
'../../../submodules/c_fsio/src/fsio.c',
install: false, dependencies: [
    c_string_buffer_dep,
  ], 
  include_directories: [
    '../../../submodules/c_string_buffer/include',
    '../../../submodules/c_fsio/src',
    '../../../submodules/c_fsio/include',
  ]
)
c_fsio_dep = declare_dependency(include_directories: [
    '../../../submodules/c_string_buffer/include',
'../../../submodules/c_fsio/src',
'../../../submodules/c_fsio/include',
  ], link_with: c_fsio_lib)
#deps += b64_dep
