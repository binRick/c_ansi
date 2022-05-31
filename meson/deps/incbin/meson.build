incbin_deps = [

]
incbin_c_args = [
  '-DINCBIN_SILENCE_BITCODE_WARNING',
]
incbin_lib = library('incbin', 
  '../../../submodules/incbin/incbin.c',
  install: false, 
  dependencies: incbin_deps,
  include_directories: [
    '../../../submodules/incbin',
  ],
  c_args: incbin_c_args,
)
incbin_dep = declare_dependency(
  include_directories: [
    '../../../submodules/incbin',
  ], 
  link_with: incbin_lib,
)

incbin_headers = [
  'incbin.h',
]
