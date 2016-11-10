# This Works is placed under the terms of the Copyright Less License,
# see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.

# Funny: With -Os the binary gets larger
CFLAGS=-Wall -O3 -Wno-unused-function -Wno-error=unused-value

PROG=shellshock

.PHONY: all
all:	$(PROG)

.PHONY: install
install:
	cp $(PROG) "$(HOME)/bin/"

.PHONY: clean distclean
clean distclean:
	rm -f *.o *~ $(PROG)

