project('c_ansi',['c'],default_options: ['warning_level=0','c_std=gnu99'],
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
subdir('emojis')
subdir('ansi-codes')
subdir('ansi-utils')
subdir('ansi-rgb-utils')
subdir('term-utils')
subdir('image-utils')
subdir('string-utils')
subdir('jinja2-cli')
#//////////////////////////////////////////////////////////////////////
subdir('term-utils-test')
subdir('ansi-rgb-utils-test')
subdir('ansi-utils-test')
subdir('ansi-codes-test')
subdir('image-utils-test')
subdir('emojis-test')
#subdir('term-termpaint')
#subdir('term-termpaint-test')
#//////////////////////////////////////////////////////////////////////
