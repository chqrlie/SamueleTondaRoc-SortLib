CC = gcc
CFLAGS=-Wall -Wextra -O2 -g -Wno-unused-parameter
LINES=10000000

all: my_tester mass_tester

gen_rand_csv: test/gen_rand_csv.c
	$(CC) $(CFLAGS) -o $@ test/gen_rand_csv.c

my_tester: test/my_tester.c src/sortlib.c
	$(CC) $(CFLAGS) -o $@ test/my_tester.c src/sortlib.c

mass_tester: test/mass_tester.c src/sortlib.c
	$(CC) $(CFLAGS) -o $@ test/mass_tester.c src/sortlib.c

# <id [int]>,<field1 [string]>,<field2 [int]>,<field3 [float]>
test-$(LINES).csv: gen_rand_csv
	./gen_rand_csv -n $(LINES) > $@

test: mass_tester test-$(LINES).csv
	./mass_tester test-$(LINES).csv test-$(LINES).sorted-1-2.csv 1 2
	./mass_tester test-$(LINES).csv test-$(LINES).sorted-2-2.csv 2 2
	./mass_tester test-$(LINES).csv test-$(LINES).sorted-3-2.csv 3 2
	./mass_tester test-$(LINES).csv test-$(LINES).sorted-1-1.csv 1 1
	./mass_tester test-$(LINES).csv test-$(LINES).sorted-2-1.csv 2 1
	./mass_tester test-$(LINES).csv test-$(LINES).sorted-3-1.csv 3 1
# cannot use diff because quicksort is not stable
#	-diff -q test-$(LINES).sorted-1-1.csv test-$(LINES).sorted-1-2.csv
#	-diff -q test-$(LINES).sorted-2-1.csv test-$(LINES).sorted-2-2.csv
#	-diff -q test-$(LINES).sorted-3-1.csv test-$(LINES).sorted-3-2.csv

clean:
	rm -f my_tester mass_tester gen_rand_csv test-[1-9]*.csv
	rm -rf *.dSYM

