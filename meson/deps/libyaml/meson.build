libyaml_srcs = []
libyaml_dir = '../../../submodules/libyaml'
libyaml_version_major = '0'
libyaml_version_minor = '2'
libyaml_version_patch = '5'
libyaml_version = libyaml_version_major + '.' + libyaml_version_minor + '.' + libyaml_version_patch
libyaml_cflags = [
	'-DYAML_VERSION_MAJOR=' + libyaml_version_major,
	'-DYAML_VERSION_MINOR=' + libyaml_version_minor,
	'-DYAML_VERSION_PATCH=' + libyaml_version_patch,
	'-DYAML_VERSION_STRING="' + libyaml_version + '"',
]
libyaml_src_files = [
  'dumper.c',
  'emitter.c',
  'loader.c',
  'parser.c',
  'reader.c',
  'scanner.c',
  'writer.c',
  'yaml_private.h',
  'api.c',
]
foreach s : libyaml_src_files
  libyaml_srcs += libyaml_dir + '/src/' + s
endforeach
libyaml_lib = static_library('libyaml', 
  libyaml_srcs,
  install: false, 
  dependencies: [],
  c_args: libyaml_cflags,
  include_directories: [
    libyaml_dir, 
    libyaml_dir + '/src',
    libyaml_dir + '/include',
  ],
)
libyaml_dep = declare_dependency(
  include_directories: [],
  link_with: libyaml_lib,
)
