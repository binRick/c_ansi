project('c-ansi', ['c'],default_options: ['warning_level=0','c_std=gnu99'])
PROJECT_NAME = 'c-ansi'
config = configuration_data()
version = run_command('git', 'describe', '--tags').stdout().strip()
config.set('version', version)
add_project_arguments('-D_GNU_SOURCE', language : 'c')
add_project_arguments('-DDBG_H_DEF_ONCE', language : 'c')
add_project_arguments('-DDBG_H_NO_WARNING', language : 'c')
add_project_arguments('-DASSERTF_DEF_ONCE', language : 'c')
add_project_arguments('-DLOG_USE_COLOR', language : 'c')
add_project_arguments('-DLOG_LEVEL=TRACE', language : 'c')
add_project_arguments('-Wno-pragma-once-outside-header', language : 'c')
add_project_arguments('-Wno-incompatible-pointer-types', language : 'c')
add_project_arguments('-Wno-pointer-sign', language : 'c')
#//////////////////////////////////////////////////////////////////////
cc = meson.get_compiler('c')
#//////////////////////////////////////////////////////////////////////
m_dep = cc.find_library('m', required : true)
parson_shared_dep = dependency('parson',fallback:['parson', 'parson_shared_dep'], required: true)
subdir('meson/deps/termpaint')
subdir('meson/deps/asprintf')
subdir('meson/deps/ms')
subdir('meson/deps/bytes')
subdir('meson/deps/c_embed')
subdir('meson/deps/generic_print')
subdir('meson/deps/debug_print_h')
subdir('meson/deps/djbhash')
subdir('meson/deps/c_string_buffer')
subdir('meson/deps/c_fsio')
subdir('meson/deps/c_timer')
subdir('meson/deps/cargs')
subdir('meson/deps/cstringfn')
subdir('meson/deps/fs')
subdir('meson/deps/rgba')
subdir('meson/deps/timestamp')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-codes')
subdir('ansi-codes-test')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-utils')
subdir('ansi-utils-test')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-rgb-utils')
subdir('ansi-rgb-utils-test')
#//////////////////////////////////////////////////////////////////////
subdir('ansi')
subdir('ansi-test')
#//////////////////////////////////////////////////////////////////////
subdir('term-utils')
subdir('term-utils-test')
#//////////////////////////////////////////////////////////////////////
c_ansi_deps = [
  ansi_codes_dep,  
  ansi_utils_dep,  
  term_utils_dep,  
]
c_ansi_include_dirs = [
]
c_ansi_lib = library(PROJECT_NAME,
  install: false,
  dependencies: c_ansi_deps,
  include_directories: c_ansi_include_dirs,
)
c_ansi_dep = declare_dependency(
  include_directories: c_ansi_include_dirs,
  link_with: c_ansi_lib,
)
#//////////////////////////////////////////////////////////////////////
