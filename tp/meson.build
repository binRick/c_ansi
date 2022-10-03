tp_srcs = [
  'tp.c',
  'tp-message-box.c',
  'term-termpaint.c',
  'tp-utils.c',
  'tp-internal.c',
  'tp-selection.c',
  'tp-tab.c',
]

tp_include_dirs = [
  '.',
    inc,
]

tp_deps = [
  termpaint_dep,  
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
  c_dbg_dep,  
]

tp_lib = library('tp',
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
