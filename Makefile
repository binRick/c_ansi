default: all
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
			   vt100-*/*.c vt100-*/*.h \
			   term-utils-test/*.c term-utils-test/*.h \
			   image-*/*.c image-*/*.h \
			   tp*/*.c tp*/*.h \
			   tai64n*/*.c tai64n*/*.h \
			   *emoji*/*.c *emoji*/*.h
##############################################################
include submodules/c_deps/etc/includes.mk

kill-rogue-tp-tests:
	@ps ax|grep '/tp-test$$'|cut -d' ' -f1|while read -r p; do if ps -o ppid= $$p|tr -d ' ' |grep '^1$$'; then kill -9 $$p; fi; done
