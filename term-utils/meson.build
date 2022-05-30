term_utils_srcs = [
  'term-utils.c',
]
term_utils_include_dirs = [
  '../submodules/termpaint',
]

term_utils_deps = [
     termpaint_dep,
]

term_utils_lib = static_library('term-utils',
  term_utils_srcs,
  install: false,
  dependencies: term_utils_deps,
  include_directories: [
    term_utils_include_dirs,
  ],
)

term_utils_dep = declare_dependency(
  include_directories: term_utils_include_dirs,
  link_with: term_utils_lib,
)
