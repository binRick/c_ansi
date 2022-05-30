asprintf_lib = library('asprintf', 
'../../../submodules/asprintf/asprintf.c',
install: false, dependencies: [
  ], 
  include_directories: [
    '../../../submodules/asprintf',
  ]
)
asprintf_dep = declare_dependency(include_directories: [
    '../../../submodules/asprintf',
  ], link_with: asprintf_lib)
#deps += b64_dep
