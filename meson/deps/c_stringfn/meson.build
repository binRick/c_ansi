c_stringfn_lib = library('c_stringfn', 
'../../../submodules/c_stringfn/src/stringfn.c',
install: false, dependencies: [], 
  include_directories: [
'../../../submodules/c_stringfn/src',
'../../../submodules/c_stringfn/include',
'../../../submodules/c_stringfn',
  ]
)
c_stringfn_dep = declare_dependency(include_directories: [
'../../../submodules/c_stringfn/src',
'../../../submodules/c_stringfn/include',
'../../../submodules/c_stringfn',
  ], link_with: c_stringfn_lib)
#deps += b64_dep
