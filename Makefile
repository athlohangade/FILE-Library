project: file.o main.o testsuite.o
	cc file.o main.o testsuite.o -o project
testsuite.o: testsuite.c file.h testsuite.h
	cc testsuite.c -c
main.o: main.c file.h testsuite.h
	cc main.c -c
file.o: file.c file.h
	cc file.c -c
