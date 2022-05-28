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
##############################################################
TIDIED_FILES = \
			   ansi-test/*.c ansi-test/*.h \
			   ansi-codes/*.c ansi-codes/*.h \
			   ansi-utils/*.c ansi-utils/*.h 
#			   ansi-rgb-codes/*.c ansi-rgb-codes/*.h \
##############################################################
all: do-build
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
	@meson build || { meson build --reconfigure || { meson build --wipe; } && meson build; }
	@ninja -C build

do-test:
	@./build/ansi-test/ansi-test --test

dev: tidy nodemon
do-build: do-meson
nodemon:
	@$(PASSH) -L .nodemon.log $(NODEMON) -w '*/meson.build' --delay 1 -i '*/subprojects' -I  -w 'include/*.h' -w meson.build -w src -w Makefile -w loader/meson.build -w loader/src -w loader/include -i '*/embeds/*' -e tpl,build,sh,c,h,Makefile -x env -- bash -c 'make dev-all||true'

