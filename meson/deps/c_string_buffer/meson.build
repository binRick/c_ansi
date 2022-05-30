c_string_buffer_lib = library('c_string_buffer', 
  '../../../submodules/c_string_buffer/src/stringbuffer.c',
  install: false, 
  dependencies: [], 
  include_directories: [
  '../../../submodules/c_string_buffer',
  '../../../submodules/c_string_buffer/src',
  '../../../submodules/c_string_buffer/include',
  ]
)
c_string_buffer_dep = declare_dependency(include_directories: 
  [
  '../../../submodules/c_string_buffer',
  '../../../submodules/c_string_buffer/src',
  '../../../submodules/c_string_buffer/include',
    ], 
  link_with: c_string_buffer_lib)
#deps += stringbuffer_dep
