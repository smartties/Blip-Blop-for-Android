#ifndef IO_H
#define IO_H

#define _O_BINARY 0x0
#define _O_RDONLY O_RDONLY

int _open(const char* filename, int mode);
int _read(int fd, void* buf, int size);
int _close(int fd);

#endif
