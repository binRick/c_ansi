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
			   submodules/c_deps/submodules/vt100utils/vt100utils.h \
			   submodules/c_deps/submodules/vt100utils/demos/tuibox.h \
			   image-*/*.c image-*/*.h \
			   tai64n*/*.c tai64n*/*.h \
			   *emoji*/*.c *emoji*/*.h
##############################################################
include submodules/c_deps/etc/includes.mk
