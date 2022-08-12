#!/usr/bin/env bash
set -eou pipefail
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd ../.
nodemon -V -I -w ./build -x bash -- -c 'reset; ./build/term-termpaint-test/term-termpaint-test'
