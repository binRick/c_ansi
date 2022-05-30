djbhash_lib = library('djbhash', 
    '../../../submodules/djbhash/src/djbhash.c', 
    install: false, dependencies: [], 
    include_directories: [
        '../../../submodules/djbhash/src',
    ]
)

djbhash_dep = declare_dependency(include_directories: [
        '../../../submodules/djbhash/src',
    ], link_with: djbhash_lib
)

#deps += djbhash_dep
