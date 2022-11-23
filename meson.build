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
    'ansi-image-utils',
    'ansi-rgb-utils',
    'submodules/c_deps/submodules',
    'submodules/c_deps/submodules/termpaint',
    'submodules/c_deps',
    'submodules',
    #'submodules/c_deps/subprojects/cargs/include',
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
subdir('ansi-image-utils')
subdir('string-utils')
subdir('vt100-utils')
#//////////////////////////////////////////////////////////////////////
subdir('term-utils-test')
subdir('ansi-rgb-utils-test')
subdir('ansi-utils-test')
subdir('ansi-codes-test')
subdir('ansi-image-utils-test')
subdir('emojis-test')
subdir('vt100-utils-test')
#subdir('term-termpaint')
#subdir('term-termpaint-test')
#//////////////////////////////////////////////////////////////////////
subdir('tuibox-dev1-test')
subdir('tp')
subdir('tp-test')
subdir('iface-test')
subdir('restic-embedded-test')
subdir('chan-utils')
#subdir('chan-utils-test-test')
subdir('ansi')
subdir('sdl')
subdir('love')
subdir('hl')
subdir('kb')
subdir('view')
subdir('str')
subdir('cache')
subdir('fs')
subdir('img')
#subdir('time')
#subdir('hash')
subdir('env')
subdir('term')
subdir('exec')
subdir('rgb-test')
subdir('love-test')
subdir('kb-test')
subdir('fs-test')
subdir('exec-test')
