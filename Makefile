default: all
##############################################################
PASSH=$(shell command -v passh)
GIT=$(shell command -v git)
SED=$(shell command -v gsed||command -v sed)
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)
BLINE=$(shell command -v bline)
UNCRUSTIFY=$(shell command -v uncrustify)
PWD=$(shell command -v pwd)
FIND=$(shell command -v find)
##############################################################
DIR=$(shell $(PWD))
ANSI_CODES_DIR=$(DIR)/ansi-codes
ANSI_UTILS_DIR=$(DIR)/ansi-codes
ETC_DIR=$(DIR)/etc
DN = >/dev/null 2>&1
##############################################################
TIDIED_FILES = \
			   ansi-codes/*.c ansi-codes/*.h \
			   ansi-codes-test/*.c ansi-codes-test/*.h \
			   ansi-rgb-utils/*.c ansi-rgb-utils/*.h \
			   ansi-rgb-utils-test/*.c ansi-rgb-utils-test/*.h \
			   term-termpaint/*.c term-termpaint/*.h  \
			   term-termpaint-test/*.c term-termpaint-test/*.h  \
			   term-utils/*.c term-utils/*.h  \
			   term-utils-test/*.c term-utils-test/*.h \
			   image-*/*.c image-*/*.h 
##############################################################
all: do-build do-test
uncrustify:
	@$(UNCRUSTIFY) -c $(ETC_DIR)/uncrustify.cfg --replace $(TIDIED_FILES) 

uncrustify-clean:
	@find . -type f -name "*unc-back*"|xargs -I % unlink %

fix-dbg:
	@$(SED) 's|, % s);|, %s);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % lu);|, %lu);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % d);|, %d);|g' -i $(TIDIED_FILES)
	@$(SED) 's|, % zu);|, %zu);|g' -i $(TIDIED_FILES)

tidy: uncrustify uncrustify-clean fix-dbg rm-make-logs
clean: 
	@rm -rf build
do-meson:
	@eval cd . && {  meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; }	
rm-make-logs:
	@rm .make-log* 2>/dev/null||true
test: do-test
build: do-meson
dev: nodemon
do-build: do-meson
	@meson compile -C build
do-test:
	@passh meson test -C build -v --print-errorlogs	
nodemon:
	@$(PASSH) -L .nodemon.log $(NODEMON) \
		-i build \
		-w submodules \
		-w "ansi-rgb-utils-test/*.c"  \
		-w "ansi-rgb-utils/*.c"  \
		-w "*/*.c" -w '*/meson.build' --delay 1 -i '*/subprojects' -I  -w 'include/*.h' -w meson.build -w src -w Makefile -w loader/meson.build -w loader/src -w loader/include -i '*/embeds/*' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'reset;make||true'
meson-introspect-all:
	@meson introspect --all -i meson.build
meson-introspect-targets:
	@meson introspect --targets -i meson.build
meson-binaries:
	@meson introspect --targets  meson.build -i | jq 'map(select(.type == "executable").filename)|flatten|join("\n")' -Mrc|xargs -I % echo ./build/%
run-binary:
	@make meson-binaries | fzf --reverse | xargs -I % passh "./%"
git-pull:
	@git pull --recurse-submodules
git-submodules-pull:
	@git submodule foreach git pull origin master --jobs=10

meson-tests-list:
	@meson test -C build --list
meson-tests:
	@make meson-tests-list|fzf --reverse -m | xargs -I % env cmd="\
		meson test --num-processes 1 -C build -v --no-stdsplit --print-errorlogs \"%\"" \
			env bash -c '\
	eval "$$cmd" && \
	ansi -n --green --bold "OK" && \
	echo -n "> " && \
	ansi -n --yellow --italic "$$cmd" && \
	echo \
'	
