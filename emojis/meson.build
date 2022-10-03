emojis_srcs = [
  'emojis.c',
  'emojis-utils.c',
]
emojis_incs = [
  inc,
  '../',
]
emojis_deps = [
  c_vector_dep,libutf8_deps,utf8_iterator_dep,
  djbhash_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  wcwidth_dep,
]


emojis_lib = library('emojis', 
  emojis_srcs,
  install: false, 
  dependencies: emojis_deps,
  include_directories: emojis_incs,
)


emojis_dep = declare_dependency(
  include_directories: emojis_incs,
  link_with: emojis_lib,
)
