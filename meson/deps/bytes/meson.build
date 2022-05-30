bytes_lib = library('bytes', 
'../../../submodules/bytes/bytes.c',
install: false, dependencies: [
  ], 
  include_directories: [
    '../../../submodules/bytes',
  ]
)
bytes_dep = declare_dependency(include_directories: [
'../../../submodules/bytes',
  ], link_with: bytes_lib)
#deps += b64_dep
