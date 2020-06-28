#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct MYFILE {
	int fd;				//file descriptor
	char rbuf[1024];		//main buffer
	int bufno;			//bufno stores the count of the buffer loaded. It increments after every 1024 bytes 
	char *rptr;			//pointer than moves along the buffer to read and write data in buffer
	int rbufcnt;			//stores the position of rptr. It varies between 0 to 1023
	off_t lastpositionbackup;	//for append+ mode, if the buffer doesn't get full, then data is written from "lastpositionbackup" to the current rbufcnt 
	off_t rpos;			//main file pointer position 
	int mode;			//mode flag : r = 0, w = 1, a = 2, r+ = 3, w+ = 4,, a+ = 5 
	off_t filelength;		//stores filelength
	int eofflag;
}MYFILE;
MYFILE *myfopen(char *pathname, char *mode);
int myfread(void *data, int size, int group, MYFILE *filedes);
int myfwrite(void *data, int size, int group, MYFILE *filedes);
int myfclose(MYFILE *filedes);
int myfseek(MYFILE *filedes, long offset, int origin);
long myftell(MYFILE *filedes);
int myfgetpos(MYFILE *filedes, off_t *ptr);
int myfsetpos(MYFILE *filedes, off_t *ptr);
int myfeof(MYFILE *fdes);
