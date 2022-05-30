ms_lib = library('ms', 
'../../../submodules/ms/ms.c',
install: false, dependencies: [
  asprintf_dep,
  ], 
  include_directories: [
    '../../../submodules/ms',
    '../../../submodules',
    '../../../submodules/asprintf',
  ]
)
ms_dep = declare_dependency(include_directories: [
'../../../submodules/ms',
  ], link_with: ms_lib)
#deps += b64_dep
