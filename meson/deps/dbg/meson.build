dbg_lib = library('dbg', 
'../../../submodules/dbg/dbg.h',
install: false, dependencies: [
  asprintf_dep,
  ], 
  include_directories: [
    '../../../submodules/dbg',
    '../../../submodules',
  ]
)
dbg_dep = declare_dependency(include_directories: [
'../../../submodules/dbg',
  ], link_with: dbg_lib)
#deps += b64_dep
