b64_lib = library('b64', 
'../../../submodules/b64.c/buffer.c',
'../../../submodules/b64.c/encode.c',
'../../../submodules/b64.c/decode.c',
install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/b64.c',
  ]
)
b64_dep = declare_dependency(include_directories: ['../../../submodules/b64.c'], link_with: b64_lib)
#deps += b64_dep
