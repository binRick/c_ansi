cstructs_json_deps = [
]

cstructs_json_c_args = [
]

cstructs_json_srcs = [

]

cstructs_json_lib = library('cstructs_json',  cstructs_json_srcs,
  install: false, 
  dependencies: cstructs_json_deps,
  include_directories: [
    '../../../submodules/cstructs-json',
  ],
  c_args: cstructs_json_c_args,
)
cstructs_json_dep = declare_dependency(
  include_directories: [
    '../../../submodules/cstructs-json',
  ], 
  link_with: cstructs_json_lib,
)

cstructs_json_headers = [
]
