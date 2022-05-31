http_get_lib = static_library('http-get', 
  '../../../submodules/http-get.c/src/http-get.c',
  install: false, 
  dependencies: [], 
  include_directories: [
    '../../../submodules/http-get.c/src',
  ]
)
http_get_dep = declare_dependency(include_directories: ['../../../submodules/http-get.c/src'], link_with: http_get_lib)
