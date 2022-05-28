project('c_ansi', ['c'],default_options: ['warning_level=0','c_std=gnu99'])
config = configuration_data()
version = run_command('git', 'describe', '--tags')
config.set('version', version.stdout().strip())
add_project_arguments('-D_GNU_SOURCE', language : 'c')
add_project_arguments('-DDBG_H_DEF_ONCE', language : 'c')
add_project_arguments('-DDBG_H_NO_WARNING', language : 'c')
add_project_arguments('-DASSERTF_DEF_ONCE', language : 'c')
add_project_arguments('-DLOG_USE_COLOR', language : 'c')
add_project_arguments('-DLOG_LEVEL=TRACE', language : 'c')
add_project_arguments('-Wno-pragma-once-outside-header', language : 'c')
add_project_arguments('-Wno-incompatible-pointer-types', language : 'c')
add_project_arguments('-Wno-pointer-sign', language : 'c')
cc = meson.get_compiler('c')
#//////////////////////////////////////////////////////////////////////
m_dep = cc.find_library('m', required : true)
subdir('ansi-codes')
#subdir('ansi-utils')
#subdir('ansi-rgb-utils')
c_ansi_deps = [
  ansi_codes_dep,  
  #  ansi_utils_dep,  
  #  ansi_rgb_dep,  
]
#//////////////////////////////////////////////////////////////////////

subdir('ansi-test')
subdir('ansi')
