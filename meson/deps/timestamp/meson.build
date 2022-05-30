timestamp_lib = library('timestamp', 
  '../../../submodules/timestamp/timestamp.c',
    install: false,
  dependencies: [],
  include_directories: [
  '../../../submodules/timestamp',
  ]
)
timestamp_dep = declare_dependency(include_directories: [], link_with: timestamp_lib)
