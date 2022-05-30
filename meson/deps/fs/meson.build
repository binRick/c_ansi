fs_lib = library('fs', 
'../../../submodules/fs.c/fs.c',
install: false, dependencies: [], 
  include_directories: [
'../../../submodules/fs.c',
  ]
)
fs_dep = declare_dependency(include_directories: [
'../../../submodules/fs.c',
  ], link_with: fs_lib)
#deps += b64_dep
