#!/usr/bin/env bash
set -eou pipefail
set -x
BF=$(pwd)/bin/yaml2json

do_test() {
	$BF --help
}
do_build() {
	if [[ ! -d .venv ]]; then
		python3 -m venv .venv
	fi
	source $(pwd)/.venv/bin/activate
	pip install pip -U
	pip install stickytape cython json2yaml

	LOC=.venv/bin
	PF=$LOC/yaml2json
	CF=$LOC/yaml2json.c

	cython --embed -v --lenient --fast-fail $PF
	gcc -Os $(python-config --include --cflags --ldflags) $CF -o $BF-py2
	gcc $(pkg-config --libs --cflags python3-embed) $CF -o ${BF}-py3

	cp ${BF}-py3 $BF
}
[[ -e "$BF" ]] || do_build

otool -L bin/yaml2json*

test
