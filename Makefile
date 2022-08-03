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
			   jinja*/*.c jinja*/*.h\
			   term-utils/*.c term-utils/*.h  \
			   term-utils-test/*.c term-utils-test/*.h \
			   image-*/*.c image-*/*.h 
##############################################################
all: do-build do-test muon
do-muon-setup:
	@muon setup build-muon
do-muon-clean:
	@rm -rf build-muon
do-muon-build:
	@muon samu -C build-muon
do-muon-install:
	@cd build-muon && muon install
do-muon-test:
	@cd build-muon && muon test
build-muon: do-muon-setup do-muon-build do-muon-test
muon: build-muon
	
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
clean:  do-muon-clean
	@rm -rf build
do-meson:
	@eval cd . && {  meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }; }	
rm-make-logs:
	@rm .make-log* 2>/dev/null||true
test: do-test
build: do-meson muon
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

git-pull:
	@git pull --recurse-submodules
git-submodules-pull:
	@git submodule foreach git pull origin master --jobs=10

run-binary:
	@clear; make meson-binaries | env FZF_DEFAULT_COMMAND= \
        fzf --reverse \
            --preview-window='follow,wrap,right,80%' \
            --bind 'ctrl-b:preview(make meson-build)' \
            --preview='env bash -c {} -v -a' \
            --ansi --border \
            --cycle \
            --header='Select Test Binary' \
            --height='100%' \
    | xargs -I % env bash -c "./%"
run-binary-nodemon:
	@make meson-binaries | fzf --reverse | xargs -I % nodemon -w build --delay 1000 -x passh "./%"
meson-tests-list:
	@meson test -C build --list
meson-tests:
	@{ make meson-tests-list; } |fzf \
        --reverse \
        --bind 'ctrl-b:preview(make meson-build)' \
        --bind 'ctrl-t:preview(make meson-tests-list)'\
        --bind 'ctrl-l:reload(make meson-tests-list)'\
        --bind 'ctrl-k:preview(make clean meson-build)'\
        --bind 'ctrl-y:preview-half-page-up'\
        --bind 'ctrl-u:preview-half-page-down'\
        --bind 'ctrl-/:change-preview-window(right,80%|down,90%,border-horizontal)' \
        --preview='\
            meson test --num-processes 1 -C build -v \
                --no-stdsplit --print-errorlogs {}' \
        --preview-window='follow,wrap,bottom,85%' \
        --ansi \
        --header='Select Test Case |ctrl+b:rebuild project|ctrl+k:clean build|ctrl+t:list tests|ctrl+l:reload test list|ctrl+/:toggle preview style|ctrl+y/u:scroll preview|'\
        --header-lines=0 \
        --height='100%'
