string_utils_srcs = [
  'string-utils.c',
]
string_utils_include_dirs = [
  '.',
  inc,
]

string_utils_deps = [
  c_stringfn_dep,
  c_vector_dep,
  c_string_buffer_dep,sha256_c_dep,c_fsio_dep,c_string_buffer_dep,b64_dep,
]

string_utils_lib_static = static_library('string-utils',
  string_utils_srcs,
  install: false,
  dependencies: string_utils_deps,
  include_directories: string_utils_include_dirs,
)
string_utils_c_args = [
  '-Wno-incompatible-pointer-types-discards-qualifiers',
  ]

string_utils_lib = shared_library('string-utils',
  string_utils_srcs,
  install: false,
  dependencies: string_utils_deps,
  include_directories: string_utils_include_dirs,
  c_args: string_utils_c_args,
)

string_utils_dep = declare_dependency(
  include_directories: string_utils_include_dirs,
  link_with: string_utils_lib,
  link_args: osx_ldflags,
)
