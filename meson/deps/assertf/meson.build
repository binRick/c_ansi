assertf_lib = library('assertf', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/assertf',
    ]
)

assertf_dep = declare_dependency(include_directories: [
        '../../../submodules/assertf',
    ], 
    link_with: assertf_lib
)

#deps += assertf_dep
