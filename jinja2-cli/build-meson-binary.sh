#!/usr/bin/env bash
set -eou pipefail
set -x
BF=$(pwd)/bin/meson

do_test() {
	$BF --help
}
do_build() {
	if [[ ! -d .venv ]]; then
		python3 -m venv .venv
	fi
	source $(pwd)/.venv/bin/activate
	pip install pip -U
	pip install stickytape cython meson

	LOC=.venv/lib/python3.9/site-packages
	PF=$LOC/mesonbuild/mesonmain.py
	CF=$LOC/mesonbuild/mesonmain.c

	cython --embed -v --lenient --fast-fail $PF
	gcc -Os $(python-config --include --cflags --ldflags) $CF -o $BF-py2
	gcc $(pkg-config --libs --cflags python3-embed) $CF -o ${BF}-py3

	cp ${BF}-py3 $BF
}
[[ -e "$BF" ]] || do_build

otool -L bin/meson*

test
