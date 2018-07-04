Xdocpath=./doc/api

CFLAGS+=-Wall -Wextra -std=gnu99 -pedantic -g -I"$(PWD)/include"
#CFLAGS+=-DUPO_DEBUG
#LDLIBS+=-lrt
#apps_targets=
#bin_targets=
#test_targets=

export CFLAGS
#export apps_targets
#export bin_targets
#export test_targets

#include mk/*.mk

.PHONY: all apps bin clean doc

all: bin apps

bin:
	cd bin && $(MAKE) all

apps: bin
	cd apps && $(MAKE) all

test: bin
	cd test && $(MAKE) all

doc:
	mkdir -p $(docpath)
	doxygen

clean:
	cd bin && $(MAKE) clean
	cd apps && $(MAKE) clean

doc-clean:
	$(RM) -r $(docpath)

realclean: clean doc-clean
