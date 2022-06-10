term_termpaint_srcs = [
  'term-termpaint.c',
]

term_termpaint_include_dirs = [
  '../submodules/termpaint',
  '../',
  '../submodules',
  '../submodules/c_palettes',
  '../submodules/c_palettes/palettes',
  '../submodules/c_palettes/palette-utils',
]

term_termpaint_deps = [
  c_stringfn_dep,  
  #palette_utils_dep,  
  termpaint_dep,
  palettes_dep,
]

term_termpaint_lib = library('term-termpaint',
  term_termpaint_srcs,
  install: false,
  dependencies: term_termpaint_deps,
  include_directories: [
    term_termpaint_include_dirs,
  ],
)

term_termpaint_dep = declare_dependency(
  include_directories: term_termpaint_include_dirs,
  link_with: term_termpaint_lib,
)
