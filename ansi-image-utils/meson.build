ansi_image_utils_srcs = [
  'ansi-image-utils.c',
]
ansi_image_utils_include_dirs = [
  inc,
]

ansi_image_utils_deps = [
  ansi_utils_dep,
]

ansi_image_utils_lib = library('image-utils',
  ansi_image_utils_srcs,
  install: false,
  dependencies: ansi_image_utils_deps,
  include_directories: ansi_image_utils_include_dirs,
)

ansi_image_utils_dep = declare_dependency(
  include_directories: ansi_image_utils_include_dirs,
  link_with: ansi_image_utils_lib,
)
