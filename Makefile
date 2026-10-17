# Copyright (c) 2019-2021 Robert Ryszard Paciorek <rrp@opcode.eu.org>
# 
# MIT License
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

MAINDIR     := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
OUTDIR      := $(MAINDIR)/output-www
TEXBUILDDIR := $(MAINDIR)/tmp-build
LIBFILESDIR := $(MAINDIR)/OpCode-core/lib

CORE := $(MAINDIR)/OpCode-core
include $(shell if [ ! -f "$(CORE)/Makefile" ]; then git submodule update --init "$(CORE)" > /dev/null; fi; echo "$(CORE)/Makefile")

.PHONY: init installDependencies all upload serve

init: | checkout-submodules
	@ echo "init done"

installDependencies:
	$(SUDO_CMD) make installCoreDependencies
	$(SUDO_CMD) apt install -y  texlive-latex-extra

all:
	[ "$(realpath $(MAINDIR))" = "$(realpath $(PWD))" ] # fail when run from wrong directory
	(cd vademecum    && $(MAKE) -f ../Makefile buildAll)
	(cd output-www; rm -f offline.tar.xz; tar -chJf ../tmp-build/offline.tar.xz .; mv ../tmp-build/offline.tar.xz .; ln -sf offline.tar.xz vademecum.tar.xz)

serve:
	cd $(OUTDIR) && python3 -m http.server

upload:
	cd $(OUTDIR); ln -sf vademecum.xhtml index.xhtml
	cd $(OUTDIR); rsync -rLc --delete -v -e "ssh" ./ www.opcode.eu.org:/srv/WebPages/vip/

#
# addionals files
#

include $(MAINDIR)/vademecum/Makefile
