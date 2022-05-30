c_embed_lib = library('c_embed', 
'../../../submodules/c_embed/loader/include/embeds.h',
install: false, dependencies: [
  asprintf_dep,
  ], 
  include_directories: [
    '../../../submodules/c_embed/loader/include',
    '../../../submodules/c_embed/loader',
    '../../../submodules/c_embed',
    '../../../submodules',
  ]
)
c_embed_dep = declare_dependency(include_directories: [
'../../../submodules/c_embed',
  ], link_with: c_embed_lib)
#deps += b64_dep
