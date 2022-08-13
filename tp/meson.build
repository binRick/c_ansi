tp_srcs = [
  'tp.c',
]

tp_include_dirs = [
  '.',
    inc,
]

tp_deps = [
  termpaint_dep,  
  termpaint_image_dep,  
  c_stringfn_dep,  
  c_string_buffer_dep,  
  ansi_codes_dep,  
  timestamp_dep,  
  module_dep,
  c_vector_dep,
  c_string_buffer_dep,
  c_stringfn_dep,
  uuid4_dep,
  ansi_codes_dep,
  wildcardcmp_dep,
  tiny_regex_c_dep,
  ansi_utils_dep,  
]

tp_lib = both_libraries('tp',
  tp_srcs,
  install: false,
  dependencies: tp_deps,
  include_directories: [
    tp_include_dirs,
  ],
)

tp_dep = declare_dependency(
  include_directories: tp_include_dirs,
  link_with: tp_lib,
)
