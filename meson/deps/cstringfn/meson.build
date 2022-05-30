cstringfn_lib = library('cstringfn', 
'../../../submodules/c_stringfn/src/stringfn.c',
install: false, dependencies: [], 
  include_directories: [
'../../../submodules/c_stringfn/src',
'../../../submodules/c_stringfn/include',
'../../../submodules/c_stringfn',
  ]
)
cstringfn_dep = declare_dependency(include_directories: [
'../../../submodules/c_stringfn/src',
'../../../submodules/c_stringfn/include',
'../../../submodules/c_stringfn',
  ], link_with: cstringfn_lib)
#deps += b64_dep
