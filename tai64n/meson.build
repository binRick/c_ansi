tai64n_srcs = [
  'tai64n.c',
]
tai64n_incs = [
  inc,
  '.',
]
tai64n_deps = [
]


tai64n_lib = static_library('tai64n', 
  tai64n_srcs,
  install: false, 
  dependencies: tai64n_deps,
  include_directories: tai64n_incs,
)


tai64n_dep = declare_dependency(
  include_directories: tai64n_incs,
  link_with: tai64n_lib,
)
