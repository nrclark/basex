SOURCES := basex.c walk.c walk.h stack.c stack.h

default: test

test: basex
	./$^ . ".*[.]c$$"

basex: $(SOURCES)
	gcc -O2 -Wall -Wextra -Wno-format $(filter %.c,$^) -o $@
	
basex_valgrind: $(SOURCES)
	gcc -O0 -g3 -Wall -Wextra -Wno-format $(filter %.c,$^) -o $@
	
memcheck: basex_valgrind
	valgrind --leak-check=yes ./$^ . ".*[.]c$$"

clean::
	rm -f basex_valgrind basex
