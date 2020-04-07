MAINDIR     := $(dir $(lastword $(MAKEFILE_LIST)))
OUTDIR      := $(MAINDIR)/output-www
TEXBUILDDIR := $(MAINDIR)/output-tmp
LIBFILESDIR := $(MAINDIR)/OpCode-core/lib
SVGICONURL  := https://bytebucket.org/OpCode-eu-org/svgiconset/raw/HEAD/other/
export PATH := $(shell realpath $(MAINDIR)/TextUtils/convert):$(PATH)


all: | check-submodules
	cd vademecum; $(MAKE) -f ../Makefile buildAll

installDependencies:
	cd $(MAINDIR)/TextUtils && make installDependencies
	@ if ! which sch2img.sh > /dev/null; then \
		echo "Cant't find sch2img.sh in PATH"; \
		echo "You should download and install EDA libs (with dependencies!) from https://bitbucket.org/OpCode-eu-org/eda-libs"; \
		return 3; \
	fi

upload:
	cd $(OUTDIR); ln -sf vademecum.xhtml index.xhtml
	cd $(OUTDIR); rsync -rLc --delete -v -e "ssh" ./ www.opcode.eu.org:/srv/WebPages/vip/

#
# submodules
#

.PHONY: check-submodules update-submodules

check-submodules: $(MAINDIR)/OpCode-core/lib/base.css $(MAINDIR)/TextUtils/convert/xml2xhtml.py

$(MAINDIR)/OpCode-core/% $(MAINDIR)/TextUtils/%:
	git submodule update --init
	[ -e "$@" ] || $(MAKE) update-submodules
	chmod 111 `git submodule | awk '{print $$2}'`

update-submodules:
	git submodule foreach git pull origin master
	git submodule foreach git checkout -f .

#
# include core makefile from TextUtils
#

-include $(MAINDIR)/TextUtils/makefiles/buildWebSite.mk
