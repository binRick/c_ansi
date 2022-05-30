generic_print_lib = library('generic_print', 
'../../../submodules/generic-print/print.h',
install: false, dependencies: [
  asprintf_dep,
  ], 
  include_directories: [
  ]
)
generic_print_dep = declare_dependency(include_directories: [
'../../../submodules/generic-print',
  ], link_with: generic_print_lib)
#deps += b64_dep
