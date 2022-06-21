project('c_ansi',['c'],default_options: ['warning_level=3','c_std=gnu99'])
cc = meson.get_compiler('c')
meson_deps_dir = join_paths(meson.current_source_dir(), 'submodules/meson_deps')
pwd = meson.current_source_dir()
inc = [
  include_directories(
    './submodules/meson_deps/submodules/c_palettes',
    './submodules/meson_deps/submodules',
    './submodules/meson_deps',
    './submodules',
    './subprojects',
    './',
  ),
]
#############################################################################
subdir('submodules/meson_deps/meson/args')
subdir('submodules/meson_deps/meson/inc')
subdir('submodules')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-codes')
subdir('ansi-codes-test')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-rgb-utils')
subdir('ansi-rgb-utils-test')
#//////////////////////////////////////////////////////////////////////
subdir('ansi-utils')
subdir('ansi-utils-test')
#//////////////////////////////////////////////////////////////////////
subdir('term-utils')
subdir('term-utils-test')
#//////////////////////////////////////////////////////////////////////
subdir('image-utils')
subdir('image-utils-test')
#//////////////////////////////////////////////////////////////////////
#subdir('term-termpaint')
#subdir('term-termpaint-test')
#//////////////////////////////////////////////////////////////////////
#subdir('ansi')
#subdir('ansi-test')
#//////////////////////////////////////////////////////////////////////
