default: all
##############################################################
include submodules/c_deps/etc/tools.mk
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
			   image-*/*.c image-*/*.h \
			   tai64n*/*.c tai64n*/*.h \
			   *emoji*/*.c *emoji*/*.h
##############################################################
include submodules/c_deps/etc/includes.mk
all: do-build do-test muon
rm-make-logs:
	@rm .make-log* 2>/dev/null||true
test: do-test
dev: nodemon
nodemon:
	@$(PASSH) -L .nodemon.log $(NODEMON) \
		-i build \
		-w submodules \
		-w "ansi-rgb-utils-test/*.c"  \
		-w "ansi-rgb-utils/*.c"  \
		-w "*/*.c" -w '*/meson.build' --delay 1 -i '*/subprojects' -I  -w 'include/*.h' -w meson.build -w src -w Makefile -w loader/meson.build -w loader/src -w loader/include -i '*/embeds/*' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'reset;make||true'

git-pull:
	@git pull --recurse-submodules
git-submodules-pull:
	@git submodule foreach git pull origin master --jobs=10

