c_timer_lib = library('c_timer', 
'../../../submodules/c_timer/include/c_timer.h',
install: false, dependencies: [
  ], 
  include_directories: [
    '../../../submodules/c_timer/include',
    '../../../submodules/c_timer',
  ]
)
c_timer_dep = declare_dependency(include_directories: [
    '../../../submodules/c_timer/include',
    '../../../submodules/c_timer',
    '../../../',
  ], link_with: c_timer_lib)
#deps += b64_dep
