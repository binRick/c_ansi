default: all
##############################################################
include submodules/c_deps/etc/includes.mk

kill-rogue-tp-tests:
	@ps ax|grep '/tp-test$$'|cut -d' ' -f1|while read -r p; do if ps -o ppid= $$p|tr -d ' ' |grep '^1$$'; then kill -9 $$p; fi; done
