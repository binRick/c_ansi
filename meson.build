project('c_ansi',['c'],
  default_options: ['warning_level=0','c_std=gnu99','default_library=static'],
  subproject_dir: 'submodules/c_deps/subprojects',  
  version: '0.0.1',
  )
passh_program = find_program('passh', required : true)
cc = meson.get_compiler('c')
c_deps_dir = join_paths(meson.current_source_dir(), 'submodules/c_deps')
pwd = meson.current_source_dir()
inc = [
  include_directories(
    'ansi-codes',
    'ansi-utils',
    'term-utils',
    'image-utils',
    'ansi-rgb-utils',
    'submodules/c_deps/submodules',
    'submodules/c_deps/submodules/termpaint',
    'submodules/c_deps',
    'submodules',
    'submodules/c_deps/subprojects/cargs/include',
    'submodules/c_deps/submodules/c_embed/embeds',
    'submodules/c_deps/submodules/c_embed',
    'submodules/c_deps/submodules/c_palettes',
    '.',
  ),
]
#############################################################################
subdir('submodules')
#//////////////////////////////////////////////////////////////////////
subdir('tai64n')
subdir('emojis')
subdir('ansi-utils')
subdir('ansi-codes')
subdir('ansi-rgb-utils')
subdir('term-utils')
subdir('image-utils')
subdir('string-utils')
subdir('jinja2-cli')
subdir('vt100-utils')
#//////////////////////////////////////////////////////////////////////
subdir('term-utils-test')
subdir('ansi-rgb-utils-test')
subdir('ansi-utils-test')
subdir('ansi-codes-test')
subdir('image-utils-test')
subdir('emojis-test')
subdir('vt100-utils-test')
#subdir('term-termpaint')
#subdir('term-termpaint-test')
#//////////////////////////////////////////////////////////////////////
subdir('tuibox-dev1-test')
subdir('richard-wow1-test')
subdir('tp')
subdir('tp-test')
