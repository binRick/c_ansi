term_termpaint_srcs = [
  'term-termpaint.c',
]

term_termpaint_include_dirs = [
  inc,
]

term_termpaint_deps = [
  c_stringfn_dep,  
  termpaint_dep,
]

term_termpaint_lib = static_library('term-termpaint',
  term_termpaint_srcs,
  install: false,
  dependencies: term_termpaint_deps,
  include_directories: term_termpaint_include_dirs,
)

term_termpaint_dep = declare_dependency(
  include_directories: term_termpaint_include_dirs,
  link_with: term_termpaint_lib,
)
