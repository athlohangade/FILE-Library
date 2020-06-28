#include "file.h"
#include "testsuite.h"
int main() {
	printf("READ MODE TESTING : \n");
	testsuiteread();
	printf("WRITE MODE TESTING : \n");
	testsuitewrite();
	printf("APPEND MODE TESTING : \n");
	testsuiteappend();
	printf("READ+ MODE TESTING : \n");
	testsuitereadplus();
	printf("WRITE+ MODE TESTING : \n");
	testsuitewriteplus();
	printf("APPEND+ MODE TESTING : \n");
	testsuiteappendplus();
	return 0;
}
