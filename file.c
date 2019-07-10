#include "file.h"
size_t getFilesize(const char* filename) {
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;   
}
MYFILE *myfopen(char *pathname, char *mode) {
	int fd;
	MYFILE *filedes;
	filedes = (MYFILE *)malloc(sizeof(MYFILE));			//To return a file pointer
	if(!strcmp(mode, "r")) {
		fd = open(pathname, O_RDONLY, S_IRUSR);
		filedes->fd = fd;
		filedes->filelength = getFilesize(pathname);
		lseek(filedes->fd, 0, 0);
		bzero(filedes->rbuf, 1024);
		filedes->bufno = 0;
		if(filedes->filelength <= 1024) {
			read(fd, filedes->rbuf, filedes->filelength);
			lseek(filedes->fd, 0, 0);
		}
		else {
			read(fd, filedes->rbuf, 1024);
			lseek(filedes->fd, 0, 0);
		}
		filedes->rptr = filedes->rbuf;
		filedes->rpos = 1;
		filedes->rbufcnt = 0;
		filedes->mode = 0;
		if(fd == -1) {			//This is to check if the opening of file is failed internally in the computer
			errno = EACCES;
			return NULL;
		}
		return filedes;
	}
	if(!strcmp(mode, "w")) {
		fd = open(pathname,  O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);	//requires read permission for loading buffer time to time
		filedes->fd = fd;
		filedes->filelength = 0;
		filedes->bufno = 0;
		bzero(filedes->rbuf, 1024);
		filedes->rbufcnt = 0;
		filedes->rptr = filedes->rbuf;
		filedes->rpos = 1;
		filedes->mode = 1;
		if(fd == -1) {
			errno = EACCES;
			return NULL;
		}
		return filedes;
	}
	if(!strcmp(mode, "a")) {
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);	
		filedes->fd = fd;
		filedes->filelength = getFilesize(pathname);
		filedes->rpos = filedes->filelength + 1;
		filedes->bufno = filedes->filelength / 1024;
		bzero(filedes->rbuf, 1024);
		filedes->mode = 2;
		filedes->rbufcnt = 0;
		filedes->rptr = filedes->rbuf;
		if(fd == -1) {
			errno = EACCES;
			return NULL;
		}
		return filedes;
	}
	if(!strcmp(mode, "r+")) {
		fd = open(pathname, O_RDWR, S_IRUSR | S_IWUSR);	
		filedes->fd = fd;
		filedes->filelength = getFilesize(pathname);
		lseek(filedes->fd, 0, 0);
		filedes->rpos = 1;
		filedes->mode = 3;
		filedes->bufno = 0;
		bzero(filedes->rbuf, 1024);
		if(filedes->filelength <= 1024) {
			read(fd, filedes->rbuf, filedes->filelength);
			lseek(filedes->fd, 0, 0);
		}
		else {
			read(fd, filedes->rbuf, 1024);
			lseek(filedes->fd, 0, 0);
		}
		filedes->rptr = filedes->rbuf;
		filedes->rbufcnt = 0;
		if(fd == -1) {
			errno = EACCES;
			return NULL;
		}
		return filedes;
	}
	if(!strcmp(mode, "w+")) {
		fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);	
		filedes->fd = fd;
		filedes->filelength = 0;
		filedes->rpos = 1;
		filedes->mode = 4;
		filedes->bufno = 0;
		bzero(filedes->rbuf, 1024);
		filedes->rptr = filedes->rbuf;
		filedes->rbufcnt = 0;
		if(fd == -1) {
			errno = EACCES;
			return NULL;
		}
		return filedes;
	}
	if(!strcmp(mode, "a+")) {
		fd = open(pathname, O_RDWR | O_CREAT | O_APPEND , S_IWUSR | S_IRUSR);	
		filedes->fd = fd;
		filedes->filelength = getFilesize(pathname);
		lseek(filedes->fd, 0, 0);
		filedes->rpos = 1;
		filedes->bufno = 0;
		bzero(filedes->rbuf, 1024);
		if(filedes->filelength <= 1024)
			read(fd, filedes->rbuf, filedes->filelength);
		else
			read(fd, filedes->rbuf, 1024);
		filedes->rptr = filedes->rbuf;
		filedes->rbufcnt = 0;
		filedes->mode = 5;
		filedes->lastpositionbackup = filedes->filelength + 1;
		if(fd == -1) {
			errno = EACCES;
			return NULL;
		}
		return filedes;
	}
	errno = EINVAL;
	return NULL;				//This NULL return will be executed if the user enters incorrect mode
}

int myfread(void *data, int size, int group, MYFILE *fdes) {
	int i;
	int sizechangeflag = 0;
	int readsize = size * group;
	char *ptr = (char *)data;
	if(fdes->mode == 1 || fdes->mode == 2){
		errno = EBADF;
		return 0;
	}
	if((fdes->mode == 0 || fdes->mode == 3 ||fdes->mode == 4 || fdes->mode == 5) && (fdes->rpos > fdes->filelength)) {
		fdes->eofflag = 1;
		return 0;
	}
	if(readsize > (fdes->filelength - fdes->rpos + 1)) {
		readsize = fdes->filelength - fdes->rpos + 1;
		sizechangeflag = 1;
		fdes->eofflag = 1;
	}
	if(fdes->mode == 0) { 
		for(i = 0; i < readsize; i++) {
			*ptr = *fdes->rptr;
			ptr++;
			fdes->rptr++;
			fdes->rbufcnt++;
			fdes->rpos++;
			if(fdes->rbufcnt == 1024) {
				fdes->bufno = fdes->bufno + 1;
				fdes->rbufcnt = 0;
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && ((fdes->filelength - fdes->rpos + 1) > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					fdes->rptr = fdes->rbuf;
				}
				else if((fdes->filelength - fdes->rpos + 1) > 0) {
					read(fdes->fd, fdes->rbuf, 1024);
					fdes->rptr = fdes->rbuf;
				}
			}
		}
	}
	if(fdes->mode == 3 || fdes->mode == 4) {
		for(i = 0; i < readsize; i++) {
			*ptr = *fdes->rptr;
			ptr++;
			fdes->rptr++;
			fdes->rbufcnt++;
			fdes->rpos++;
			if(fdes->rbufcnt == 1024) {
				lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET);
				write(fdes->fd, fdes->rbuf, 1024);
				fdes->bufno = fdes->bufno + 1;
				fdes->rbufcnt = 0;
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && ((fdes->filelength - fdes->rpos + 1) > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					fdes->rptr = fdes->rbuf;
				}
				else if((fdes->filelength - fdes->rpos + 1) > 0) {
					read(fdes->fd, fdes->rbuf, 1024);
					fdes->rptr = fdes->rbuf;
				}
			}
		}
	}
	if(fdes->mode == 5) {
		for(i = 0; i < readsize; i++) {
			*ptr = *fdes->rptr;
			ptr++;
			fdes->rptr++;
			fdes->rbufcnt++;
			fdes->rpos++;
			if(fdes->rbufcnt == 1024) {
				fdes->bufno = fdes->bufno + 1;
				fdes->rbufcnt = 0;
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && ((fdes->filelength - fdes->rpos + 1) > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					fdes->rptr = fdes->rbuf;
				}
				else if((fdes->filelength - fdes->rpos + 1) > 0) {
					read(fdes->fd, fdes->rbuf, 1024);
					fdes->rptr = fdes->rbuf;
				}
			}
		}
	}
	lseek(fdes->fd, fdes->rpos - 1, 0);
	if(sizechangeflag == 1) {
		if(size == 1)
			return (readsize / size);
		else
			return ((readsize / size) + 1);
	}
	else
		return (group);
}

int myfwrite(void *data, int size, int group, MYFILE *fdes) {
	int i;
	char *ptr = data;
	int writesize = size * group;
	if(fdes->mode == 0) {
		errno = EBADF;	
		return 0;
	}
	if(fdes->mode == 1 || fdes->mode == 3 || fdes->mode == 4) {
		if(fdes->rpos - 1 > fdes->filelength)
			fdes->filelength = fdes->rpos - 1;
		for(i = 0; i < writesize; i++) {
			*fdes->rptr = *ptr;
			ptr++;
			fdes->rptr++;
			fdes->rbufcnt++;
			if((fdes->rpos - 1) >= fdes->filelength)		//if file ptr goes ahead of eof
				fdes->filelength++;
			fdes->rpos++;
			if(fdes->rbufcnt == 1024) {
				lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET);
				write(fdes->fd, fdes->rbuf, 1024);
				fdes->bufno = fdes->bufno + 1;
				fdes->rbufcnt = 0;
				fdes->rptr = fdes->rbuf;
				bzero(fdes->rbuf, 1024);
			}
		}
	}
	if(fdes->mode == 2) {
		fdes->rpos = fdes->filelength + 1;
		for(i = 0; i < writesize; i++) {
			*fdes->rptr = *ptr;
			ptr++;
			fdes->rptr++;
			fdes->rbufcnt++;
			fdes->rpos++;
			fdes->filelength++;
			if(fdes->rbufcnt == 1024) {
				lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET);
				fdes->rpos = fdes->filelength + 1;
				write(fdes->fd, fdes->rbuf, 1024);
				fdes->bufno = fdes->bufno + 1;
				fdes->rbufcnt = 0;
				fdes->rptr = fdes->rbuf;
				bzero(fdes->rbuf, 1024);
			}
		}
	}
	if(fdes->mode == 5) {
		fdes->rpos = fdes->filelength + 1;
		if(fdes->rpos > (fdes->bufno + 1) * 1024) {
			fdes->bufno = fdes->rpos / 1024;
			lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET);
			bzero(fdes->rbuf, 1024);
			read(fdes->fd, fdes->rbuf, fdes->rpos % 1024);
		}
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		for(i = 0; i < writesize; i++) {
			*fdes->rptr = *ptr;
			ptr++;
			fdes->rptr++;
			fdes->rbufcnt++;
			fdes->rpos++;
			fdes->filelength++;
			if(fdes->rbufcnt == 1024) {
				fdes->bufno = fdes->bufno + 1;
				lseek(fdes->fd, 0, SEEK_END);
				fdes->rpos = fdes->filelength + 1;
				write(fdes->fd, &fdes->rbuf[(fdes->lastpositionbackup - 1) % 1024], 1024 - (fdes->lastpositionbackup - 1) % 1024);
				fdes->rbufcnt = 0;
				fdes->rptr = fdes->rbuf;
				bzero(fdes->rbuf, 1024);
				fdes->lastpositionbackup = fdes->bufno * 1024 + 1;
			}
		}
	}
	lseek(fdes->fd, fdes->rpos - 1, 0);
	return (group);
}

long myftell(MYFILE *fdes) {
	return fdes->rpos - 1;				//return the file pointer position
}

int myfseek(MYFILE *fdes, long offset, int origin) {
	off_t x, y, destination;
	char *str;
	if(origin == SEEK_SET && offset < 0) {
		errno = EINVAL;
		return -1;
	}
	if(origin == SEEK_CUR && (-1 * offset) >= fdes->rpos) {
		errno = EINVAL;
		return -1;
	}
	if(origin == SEEK_END && ((-1 * offset) >= fdes->filelength)) {
		errno = EINVAL;
		return -1;
	}
	if(fdes->mode == 0) {
		if(origin == SEEK_END) {
			destination = fdes->filelength + offset;
			x = fdes->rpos = (lseek(fdes->fd, destination, SEEK_SET) + 1);
		}
		else
			x = fdes->rpos = (lseek(fdes->fd, offset, origin) + 1);
		if(x <= fdes->filelength) {
			fdes->eofflag = 0;
		}
		if(fdes->rpos > fdes->filelength)
			return 0;
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		if((fdes->bufno * 1024 < fdes->rpos) && (fdes->rpos <= (fdes->bufno + 1) * 1024)) {	//if buffer remains the same no need to change it
			return 0;
		}
		fdes->bufno = (fdes->rpos - 1) / 1024;
		fdes->rpos = lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET) + 1;	// lseek for setting the buffer
		if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
			read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
		}
		else if(fdes->filelength - fdes->rpos > 1024){
			read(fdes->fd, fdes->rbuf, 1024);
		}
		fdes->rpos = lseek(fdes->fd, x - 1, SEEK_SET) + 1;	//lseek to bring back file ptr to original position
		return 0;
	}

	if(fdes->mode == 1) {
		y = fdes->rpos;
		if(origin == SEEK_END) {
			destination = fdes->filelength + offset;
			x = fdes->rpos = (lseek(fdes->fd, destination, SEEK_SET) + 1);
		}
		else
			x = fdes->rpos = (lseek(fdes->fd, offset, origin) + 1);
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		if((fdes->bufno * 1024 < fdes->rpos) && (fdes->rpos <= (fdes->bufno + 1) * 1024)) {	//if buffer remains the same no need to empty it
			return 0;
		}
		else {
			lseek(fdes->fd, 1024 * fdes->bufno , SEEK_SET);
			if(fdes->filelength < (fdes->bufno + 1) * 1024)
				write(fdes->fd, fdes->rbuf, fdes->filelength % 1024);
			else
				write(fdes->fd, fdes->rbuf, 1024);
			fdes->bufno = (fdes->rpos - 1) / 1024;
			fdes->rpos = lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET) + 1;	// lseek for setting the buffer
			if(x < y) {
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
				}
				else if(fdes->filelength - fdes->rpos > 1024){
					read(fdes->fd, fdes->rbuf, 1024);
				}
			}
			else {
				if(fdes->filelength > fdes->bufno * 1024) {
					if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
						bzero(fdes->rbuf, 1024);
						read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					}
					else if(fdes->filelength - fdes->rpos > 1024){
						read(fdes->fd, fdes->rbuf, 1024);
					}
				}
				else {
					bzero(fdes->rbuf, 1024);
				}
			}
		}
		fdes->rpos = lseek(fdes->fd, x - 1, SEEK_SET) + 1;
		return 0;
	}

	if(fdes->mode == 2) {
		if(origin == SEEK_END) {
			destination = fdes->filelength + offset;
			fdes->rpos = (lseek(fdes->fd, destination, SEEK_SET) + 1);
		}
		else
			fdes->rpos = (lseek(fdes->fd, offset, origin) + 1);
	}
	
	if(fdes->mode == 3 || fdes->mode == 4) {
		y = fdes->rpos;
		if(origin == SEEK_END) {
			destination = fdes->filelength + offset;
			x = fdes->rpos = (lseek(fdes->fd, destination, SEEK_SET) + 1);
		}
		else
			x = fdes->rpos = (lseek(fdes->fd, offset, origin) + 1);
		if(x <= fdes->filelength) {
			fdes->eofflag = 0;
		}
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		if((fdes->bufno * 1024 < fdes->rpos) && (fdes->rpos <= (fdes->bufno + 1) * 1024)) {	//if buffer remains the same no need to empty it
			return 0;
		}
		else {
			lseek(fdes->fd, 1024 * fdes->bufno , SEEK_SET);
			if(fdes->filelength < (fdes->bufno + 1) * 1024)
				write(fdes->fd, fdes->rbuf, fdes->filelength % 1024);
			else
				write(fdes->fd, fdes->rbuf, 1024);
			fdes->bufno = (fdes->rpos - 1) / 1024;
			fdes->rpos = lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET) + 1;	// lseek for setting the buffer
			if(x < y) {
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
				}
				else if(fdes->filelength - fdes->rpos > 1024){
					read(fdes->fd, fdes->rbuf, 1024);
				}
			}
			else {
				if(fdes->filelength > fdes->bufno * 1024) {
					if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
						bzero(fdes->rbuf, 1024);
						read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					}
					else if(fdes->filelength - fdes->rpos > 1024){
						read(fdes->fd, fdes->rbuf, 1024);
					}
				}
				else {
					bzero(fdes->rbuf, 1024);
				}
			}
		}
		fdes->rpos = lseek(fdes->fd, x - 1, SEEK_SET) + 1;
		return 0;
	}

	if(fdes->mode == 5) {
		y = fdes->rpos;
		str = &fdes->rbuf[fdes->lastpositionbackup % 1024 - 1];
		if(origin == SEEK_END) {
			destination = fdes->filelength + offset;
			x = fdes->rpos = (lseek(fdes->fd, destination, SEEK_SET) + 1);
		}
		else
			x = fdes->rpos = (lseek(fdes->fd, offset, origin) + 1);
		if(x <= fdes->filelength) {
			fdes->eofflag = 0;
		}
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		if((fdes->bufno * 1024 < fdes->rpos) && (fdes->rpos <= (fdes->bufno + 1) * 1024)) {	//if buffer remains the same no need to empty it
			return 0;
		}
		else {
			lseek(fdes->fd, 1024 * fdes->bufno , SEEK_SET);
			if(fdes->filelength < (fdes->bufno + 1) * 1024) {
				write(fdes->fd, str, fdes->filelength - fdes->lastpositionbackup + 1);
				fdes->lastpositionbackup = x;
			}
			fdes->lastpositionbackup = fdes->filelength + 1;
			fdes->bufno = (fdes->rpos - 1) / 1024;
			fdes->rpos = lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET) + 1;	// lseek for setting the buffer
			if(x < y) {
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
				}
				else if(fdes->filelength - fdes->rpos > 1024) {
					read(fdes->fd, fdes->rbuf, 1024);
				}
			}
			else {
				if(fdes->filelength > fdes->bufno * 1024) {
					if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
						bzero(fdes->rbuf, 1024);
						read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					}
					else if(fdes->filelength - fdes->rpos > 1024) {
						read(fdes->fd, fdes->rbuf, 1024);
					}
				}
				else {
					bzero(fdes->rbuf, 1024);
				}
			}
		}
		fdes->rpos = lseek(fdes->fd, x - 1, SEEK_SET) + 1;
		return 0;
	}	
}

int myfgetpos(MYFILE *fdes, off_t *ptr) {
	*ptr = fdes->rpos;
	return 0;
}

int myfsetpos(MYFILE *fdes, off_t *ptr) {
	off_t x, y;
	char *str;
	y = fdes->rpos;
	if(*ptr < 1) {
		errno = EINVAL;
		return -1;
	}
	x = fdes->rpos = lseek(fdes->fd, *ptr - 1, SEEK_SET) + 1;
	if(fdes->mode == 0) {
		if(x <= fdes->filelength) {
			fdes->eofflag = 0;
		}
		if(fdes->rpos > fdes->filelength)
			return 0;
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		if((fdes->bufno * 1024 < fdes->rpos) && (fdes->rpos <= (fdes->bufno + 1) * 1024)) {	//if buffer remains the same no need to change it
			return 0;
		}
		fdes->bufno = (fdes->rpos - 1) / 1024;
		fdes->rpos = lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET) + 1;	// lseek for setting the buffer
		if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
			read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
		}
		else if(fdes->filelength - fdes->rpos > 1024){
			read(fdes->fd, fdes->rbuf, 1024);
		}
		fdes->rpos = lseek(fdes->fd, x - 1, SEEK_SET) + 1;	//lseek to bring back file ptr to original position
		return 0;
	}

	if(fdes->mode == 1) {
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		if((fdes->bufno * 1024 < fdes->rpos) && (fdes->rpos <= (fdes->bufno + 1) * 1024)) {	//if buffer remains the same no need to empty it
			return 0;
		}
		else {
			lseek(fdes->fd, 1024 * fdes->bufno , SEEK_SET);
			if(fdes->filelength < (fdes->bufno + 1) * 1024)
				write(fdes->fd, fdes->rbuf, fdes->filelength % 1024);
			else
				write(fdes->fd, fdes->rbuf, 1024);
			fdes->bufno = (fdes->rpos - 1) / 1024;
			fdes->rpos = lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET) + 1;	// lseek for setting the buffer
			if(x < y) {
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
				}
				else if(fdes->filelength - fdes->rpos > 1024){
					read(fdes->fd, fdes->rbuf, 1024);
				}
			}
			else {
				if(fdes->filelength > fdes->bufno * 1024) {
					if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
						bzero(fdes->rbuf, 1024);
						read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					}
					else if(fdes->filelength - fdes->rpos > 1024){
						read(fdes->fd, fdes->rbuf, 1024);
					}
				}
				else {
					bzero(fdes->rbuf, 1024);
				}
			}
		}
		fdes->rpos = lseek(fdes->fd, x - 1, SEEK_SET) + 1;
		return 0;
	}	

	if(fdes->mode == 2) {
		return 0;
	}

	if(fdes->mode == 3 || fdes->mode == 4) {
		if(x <= fdes->filelength) {
			fdes->eofflag = 0;
		}
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		if((fdes->bufno * 1024 < fdes->rpos) && (fdes->rpos <= (fdes->bufno + 1) * 1024)) {	//if buffer remains the same no need to empty it
			return 0;
		}
		else {
			lseek(fdes->fd, 1024 * fdes->bufno , SEEK_SET);
			if(fdes->filelength < (fdes->bufno + 1) * 1024)
				write(fdes->fd, fdes->rbuf, fdes->filelength % 1024);
			else
				write(fdes->fd, fdes->rbuf, 1024);
			fdes->bufno = (fdes->rpos - 1) / 1024;
			fdes->rpos = lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET) + 1;	// lseek for setting the buffer
			if(x < y) {
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
				}
				else if(fdes->filelength - fdes->rpos > 1024){
					read(fdes->fd, fdes->rbuf, 1024);
				}
			}
			else {
				if(fdes->filelength > fdes->bufno * 1024) {
					if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
						bzero(fdes->rbuf, 1024);
						read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					}
					else if(fdes->filelength - fdes->rpos > 1024){
						read(fdes->fd, fdes->rbuf, 1024);
					}
				}
				else {
					bzero(fdes->rbuf, 1024);
				}
			}
		}
		fdes->rpos = lseek(fdes->fd, x - 1, SEEK_SET) + 1;
		return 0;
	}

	if(fdes->mode == 5) {
		if(x <= fdes->filelength) {
			fdes->eofflag = 0;
		}
		str = &fdes->rbuf[fdes->lastpositionbackup % 1024 - 1];
		fdes->rbufcnt = (fdes->rpos - 1) % 1024;
		fdes->rptr = &fdes->rbuf[fdes->rbufcnt];
		if((fdes->bufno * 1024 < fdes->rpos) && (fdes->rpos <= (fdes->bufno + 1) * 1024)) {	//if buffer remains the same no need to empty it
			return 0;
		}
		else {
			lseek(fdes->fd, 1024 * fdes->bufno , SEEK_SET);
			if(fdes->filelength < (fdes->bufno + 1) * 1024) {
				write(fdes->fd, str, fdes->filelength - fdes->lastpositionbackup + 1);
				fdes->lastpositionbackup = x;
			}
			fdes->lastpositionbackup = fdes->filelength + 1;
			fdes->bufno = (fdes->rpos - 1) / 1024;
			fdes->rpos = lseek(fdes->fd, fdes->bufno * 1024, SEEK_SET) + 1;	// lseek for setting the buffer
			if(x < y) {
				if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
					bzero(fdes->rbuf, 1024);
					read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
				}
				else if(fdes->filelength - fdes->rpos > 1024) {
					read(fdes->fd, fdes->rbuf, 1024);
				}
			}
			else {
				if(fdes->filelength > fdes->bufno * 1024) {
					if(((fdes->filelength - fdes->rpos + 1) < 1024) && (fdes->filelength - fdes->rpos > 0)) {
						bzero(fdes->rbuf, 1024);
						read(fdes->fd, fdes->rbuf, fdes->filelength - fdes->rpos + 1);
					}
					else if(fdes->filelength - fdes->rpos > 1024) {
						read(fdes->fd, fdes->rbuf, 1024);
					}
				}
				else {
					bzero(fdes->rbuf, 1024);
				}
			}
		}
		fdes->rpos = lseek(fdes->fd, x - 1, SEEK_SET) + 1;
		return 0;
	}
}

int myfeof(MYFILE *fdes) {
	if(fdes->eofflag == 1)
		return 1;
	else
		return 0;
}

int myfclose(MYFILE *fdes) {
	int x;
	char *str = &fdes->rbuf[(fdes->lastpositionbackup - 1) % 1024];
	char *ptr = &fdes->rbuf[0];
	if(fdes->mode == 5) {
		if(fdes->rbufcnt != 0) {
			if(fdes->filelength < (fdes->bufno + 1) * 1024) {
				write(fdes->fd, str, fdes->filelength - fdes->lastpositionbackup + 1);
			}
		}
	}
	else if(fdes->mode == 1 || fdes->mode == 3 || fdes->mode == 4) {
		lseek(fdes->fd, fdes->bufno * 1024, 0);
		if(fdes->filelength < fdes->rpos) {
			write(fdes->fd, ptr, fdes->filelength - (fdes->bufno * 1024));
		}
		else if((fdes->filelength > fdes->rpos) && fdes->filelength - fdes->rpos < 1024) {
			write(fdes->fd, ptr, fdes->filelength - (fdes->bufno * 1024));
		}
		else {
			write(fdes->fd, ptr, fdes->rbufcnt);
		}
	}
	else if(fdes->mode == 2) {
		if(fdes->rbufcnt != 0)
			write(fdes->fd, fdes->rbuf, fdes->rbufcnt);
	}
	x = close(fdes->fd);
	free(fdes);
	return x;
}
