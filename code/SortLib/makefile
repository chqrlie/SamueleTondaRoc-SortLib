CC = gcc

all: my_tester mass_tester

my_tester: src/sortlib.c test/my_tester.c test/support.c
	$(CC) -o my_tester.out src/sortlib.c test/my_tester.c test/support.c -I.

mass_tester: src/sortlib.c test/mass_tester.c test/support.c
	$(CC) -o mass_tester.out src/sortlib.c test/mass_tester.c test/support.c -I.