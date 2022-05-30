c_colors_lib = library('c_colors', 
'../../../submodules/c_colors/src/colors.c',
install: false, dependencies: [
    c_string_buffer_dep,
  ], 
  include_directories: [
    '../../../submodules/c_colors',
    '../../../submodules/c_colors/src',
    '../../../submodules/c_colors/include',
  ]
)
c_colors_dep = declare_dependency(include_directories: [
    '../../../submodules/c_colors',
    '../../../submodules/c_colors/src',
    '../../../submodules/c_colors/include',
  ], link_with: c_colors_lib)
#deps += b64_dep
