#!/usr/bin/env bash
set -eou pipefail
set -x
BF=$(pwd)/bin/jinja2-cli

do_test() {
	$BF --strict -o test.txt ./test.txt.jinja2 ./test.json && cat test.txt | grep '^hello world$'
}
do_build() {
	if [[ ! -d .venv ]]; then
		python3 -m venv .venv
	fi
	source $(pwd)/.venv/bin/activate
	pip install pip -U
	pip install stickytape cython jinja2-cli

	LOC="$(pip show jinja2-cli | grep ^Location | cut -d: -f2 | gsed 's/^[[:space:]]//g')"
	PF=$LOC/jinja2cli/cli.py
	CF=$LOC/jinja2cli/cli.c

	cython --embed -v --lenient --fast-fail $PF
	gcc -Os $(python-config --include --cflags --ldflags) $CF -o $BF-py2
	gcc $(pkg-config --libs --cflags python3-embed) $CF -o ${BF}-py3

	cp ${BF}-py3 $BF
}
[[ -e "$BF" ]] || do_build

otool -L bin/jinja2-cli*

test
