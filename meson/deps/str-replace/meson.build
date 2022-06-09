str_replace_lib = static_library('str-replace', 
  '../../../submodules/str-replace.c/src/str-replace.c',
  install: false, 
  dependencies: [], 
  include_directories: [
    '../../../submodules/str-replace.c/src',
  ]
)
str_replace_dep = declare_dependency(include_directories: ['../../../submodules/str-replace.c/src'], link_with: str_replace_lib)
