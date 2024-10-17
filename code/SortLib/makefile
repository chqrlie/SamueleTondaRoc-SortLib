CC = gcc

all: my_tester mass_tester

my_tester: src/sortlib.c test/my_tester.c
	$(CC) -o test_ex1.out src/sortlib.c test/my_tester.c -I.

mass_tester: src/sortlib.c test/mass_tester.c
	$(CC) -o main_ex1.out src/sortlib.c test/mass_tester.c -I.