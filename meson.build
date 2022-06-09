project('c_ansi', ['c'],default_options: ['warning_level=0','c_std=gnu99'])
config = configuration_data()
version = run_command('git', 'describe', '--tags').stdout().strip()
config.set('version', version)
add_project_arguments('-DTBL1_INCLUDED', language : 'c')
add_project_arguments('-DPRINT_H', language : 'c')
#add_project_arguments('-DASSERTF_H', language : 'c')
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
deps = []
inc = include_directories(
  'submodules',
  'submodules/c_palettes',
  'submodules/c_palettes/palettes',
  'meson/deps/c_embed',
  './',
  '../',
)
#//////////////////////////////////////////////////////////////////////
m_dep = cc.find_library('m', required : true)
curl_dep = cc.find_library('curl', required : true)
#//////////////////////////////////////////////////////////////////////
parson_shared_dep = dependency('parson',
  fallback:['parson', 'parson_shared_dep'], 
  required: true,
)
#//////////////////////////////////////////////////////////////////////
subdir('meson/deps/c_timer')
#subdir('meson/deps/assertf')
#subdir('meson/deps/str-replace')
#subdir('meson/deps/path-basename')
subdir('meson/deps/asprintf')
subdir('meson/deps/ms')
subdir('meson/deps/bytes')
subdir('meson/deps/c_embed')
subdir('meson/deps/generic_print')
subdir('meson/deps/debug_print_h')
subdir('meson/deps/djbhash')
subdir('meson/deps/c_string_buffer')
subdir('meson/deps/c_fsio')
subdir('meson/deps/cargs')
subdir('meson/deps/cstringfn')
subdir('meson/deps/fs')
subdir('meson/deps/rgba')
subdir('meson/deps/timestamp')
subdir('meson/deps/incbin')
subdir('meson/deps/cstructs_json')
subdir('meson/deps/http-get')
subdir('meson/deps/termpaint')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-codes')
subdir('ansi-codes-test')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-rgb-utils')
subdir('ansi-rgb-utils-test')
#//////////////////////////////////////////////////////////////////////
subdir('submodules/c_palettes/meson/deps/embedded_palettes')
subdir('submodules/c_palettes/palettes')
subdir('submodules/c_palettes/palette-utils')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-utils')
subdir('ansi-utils-test')
#//////////////////////////////////////////////////////////////////////
subdir('term-utils')
subdir('term-utils-test')
#//////////////////////////////////////////////////////////////////////
subdir('term-termpaint')
subdir('term-termpaint-test')
#//////////////////////////////////////////////////////////////////////
subdir('ansi')
subdir('ansi-test')
#//////////////////////////////////////////////////////////////////////
