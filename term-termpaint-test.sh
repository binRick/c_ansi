#!/usr/bin/env bash
set -eou pipefail
nodemon  -V -I -w ./build -x sh -- -c 'reset; ./build/term-termpaint-test/term-termpaint-test'
#2>.err'
