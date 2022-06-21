image_utils_srcs = [
  'image-utils.c',
]
image_utils_include_dirs = [
]

image_utils_deps = [
  ansi_utils_dep,
]

image_utils_lib = static_library('image-utils',
  image_utils_srcs,
  install: false,
  dependencies: image_utils_deps,
  include_directories: [
    image_utils_include_dirs,
  ],
)

image_utils_dep = declare_dependency(
  include_directories: image_utils_include_dirs,
  link_with: image_utils_lib,
)
