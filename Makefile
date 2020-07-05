MAINDIR     := $(dir $(lastword $(MAKEFILE_LIST)))
OUTDIR      := $(MAINDIR)/output-www
TEXBUILDDIR := $(MAINDIR)/output-tmp
LIBFILESDIR := $(MAINDIR)/OpCode-core/lib
SVGICONURL  := https://bytebucket.org/OpCode-eu-org/svgiconset/raw/HEAD/other/
export PATH := $(shell realpath $(MAINDIR)/TextUtils/convert):$(PATH)


.PHONY: help init installDependencies all upload serve
help:
	@ cd $(MAINDIR) && awk '/^#/ {x=0} x==1 {print $0} /^## Install/ {x=1}' README.md

init: | checkout-submodules
	@ echo "init done"

installDependencies:
	cd $(MAINDIR)/TextUtils && make installDependencies
	@ if ! which sch2img.sh > /dev/null; then \
		echo "Cant't find sch2img.sh in PATH"; \
		echo "You should download and install EDA libs (with dependencies!) from https://bitbucket.org/OpCode-eu-org/eda-libs"; \
		return 3; \
	fi

all:
	cd vademecum; $(MAKE) -f ../Makefile buildAll

serve:
	cd $(OUTDIR) && python3 -m http.server

upload:
	cd $(OUTDIR); ln -sf vademecum.xhtml index.xhtml
	cd $(OUTDIR); rsync -rLc --delete -v -e "ssh" ./ www.opcode.eu.org:/srv/WebPages/vip/

#
# submodules
#

.PHONY: checkout-submodules update-submodules protect-submodules

checkout-submodules:
	git submodule update --init

update-submodules: | checkout-submodules
	git submodule foreach 'git pull origin master; git checkout -f .'

protect-submodules:
	chmod 111 `git submodule | awk '{print $$2}'`
	git submodule | awk '{print $$2}' | while read sm; do git config --local "submodule.$$sm.ignore" all; done

#
# include core makefile from TextUtils
#

-include $(MAINDIR)/TextUtils/makefiles/buildWebSite.mk
