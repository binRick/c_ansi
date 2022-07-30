emojis_srcs = [
  'emojis.c',
]
emojis_incs = [
  inc,
  '../',
]
emojis_deps = [
  c_vector_dep,
  djbhash_dep,
]


emojis_lib = static_library('emojis', 
  emojis_srcs,
  install: false, 
  dependencies: emojis_deps,
  include_directories: emojis_incs,
)


emojis_dep = declare_dependency(
  include_directories: emojis_incs,
  link_with: emojis_lib,
)
