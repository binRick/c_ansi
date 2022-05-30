rgba_lib = library('rgba', 
'../../../submodules/rgba/src/rgba.c',
install: false, dependencies: [], 
  include_directories: [
    '../../../submodules/rgba',
    '../../../submodules/rgba/src',
  ]
)
rgba_dep = declare_dependency(include_directories: ['../../../submodules/rgba'], link_with: rgba_lib)
#deps += b64_dep
