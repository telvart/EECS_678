STUDENT_ID=XXXXXXX

all: bugs valgrind_test

bugs: bugs.c
	gcc -g $^ -o $@

valgrind_test: valgrind_test.c
	gcc -g $^ -o $@

test: bugs
	-valgrind --leak-check=full --track-origins=yes ./bugs > bugs_output.txt 2> valgrind_output.txt
	@sed -i 's/^==[0-9]*==/==#==/' valgrind_output.txt
	@echo ""
	@echo "======================================="
	@echo "VALGRIND DIFF"
	-@diff -a valgrind_desired.txt valgrind_output.txt
	@echo "---------------------------------------"
	@echo ""
	@echo "======================================="
	@echo "PROGRAM DIFF"
	-@diff -a bugs_desired.txt bugs_output.txt


tar: clean
	mkdir $(2760606)_eecs678_lab2
	cp bugs.c Makefile $(2760606)_eecs678_lab2
	tar cfzv $(2760606)_eecs678_lab2.tar.gz
	-rm -rf $(2760606)_eecs678_lab2

.PHONY: clean test
