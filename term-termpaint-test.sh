nodemon -V --signal SIGKILL -I -w "*/*.c" -w ./build/term-termpaint-test/term-termpaint-test -x sh -- -c 'vterm-ctrl reset;reset; ./build/term-termpaint-test/term-termpaint-test 2>.err'
