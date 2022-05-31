ansi_test_srcs = [
  'ansi-test.c',
]
ansi_test_deps = [
     c_ansi_dep, 
]

ansi_test_exec = executable('ansi-test',
   ansi_test_srcs,
   dependencies: ansi_test_deps,
   include_directories: [],
)
test('ansi-test Test', ansi_test_exec, args: [])
