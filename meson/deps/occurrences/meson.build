occurrences_lib = library('c_string_buffer', 
  '../../../submodules/occurrences.c/occurrences.c',
  install: false, 
  dependencies: [], 
  include_directories: [
  '../../../submodules/occurrences.c',
  ]
)
occurrences_dep = declare_dependency(include_directories: 
  [
  '../../../submodules/occurrences.c',
    ], 
  link_with: occurrences_lib)
#deps += stringbuffer_dep
