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
			   ansi-test/*.c ansi-test/*.h \
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

tidy: uncrustify uncrustify-clean fix-dbg         
clean: 
	@rm -rf build
do-meson:
	@meson build $(DN) \
		|| meson build --reconfigure $(DN) \
		|| meson build --wipe
	@meson build
	@ninja -C build

test: do-test

do-ninja-test:
	@ninja -C build test
	@./build/ansi-test/ansi-test  -v | ./submodules/greatest/contrib/greenest


do-test: do-ninja-test

dev: nodemon
do-build: do-meson
nodemon:
	@$(PASSH) -L .nodemon.log $(NODEMON) -w '*/meson.build' --delay 1 -i '*/subprojects' -I  -w 'include/*.h' -w meson.build -w src -w Makefile -w loader/meson.build -w loader/src -w loader/include -i '*/embeds/*' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make||true'

test-fxns:
	@grep -h '^[[:space:]].*ANSI_FXN(' ansi-test/*|cut -d, -f1|cut -d'(' -f2

test-cases:
	@grep -h '^ANSI_ARG(' ansi-test/*|cut -d, -f1|cut -d'(' -f2

test-case-commands:
	@make test-cases|xargs -I % echo ./build/ansi-test/ansi-test \-\-%

test-fxn-commands:
	@make test-fxns|xargs -I % echo ./build/ansi-test/ansi-test \-\-%

do-test-commands:
	@echo "------------------------------"
	@echo "Test Commands"
	@echo "------------------------------"
	@make test-case-commands|bash
	@echo "------------------------------"; echo

do-test-fxns:
	@echo "------------------------------"
	@echo "Test Functions"
	@echo "------------------------------"
	@eval "`make test-fxn-commands`"
	@echo "------------------------------";echo

do-tests: do-test-fxns do-test-commands
