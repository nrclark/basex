SOURCES := list_main.c list.c list.h

default: test

test: listx
	./$^ . ".*[.]c$$"

listx: $(SOURCES)
	gcc -O2 -Wall -Wextra -Wno-format $(filter %.c,$^) -o $@
	
listx_valgrind: $(SOURCES)
	gcc -O0 -g3 -Wall -Wextra -Wno-format $(filter %.c,$^) -o $@
	
memcheck: listx_valgrind
	valgrind --leak-check=yes ./$^ . ".*[.]c$$"

clean::
	rm -f listx_valgrind listx
