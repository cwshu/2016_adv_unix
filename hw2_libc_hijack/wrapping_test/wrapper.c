#define _GNU_SOURCE
// RTLD_NEXT is only supported in _GNU_SOURCE.
// _GNU_SOURCE should be at start of file. 
// I guess the reason is that it should be before first time including <feature.h>
// doesn't declare __USE_GNU by ourselves.

#include <stdio.h>

#include <unistd.h>
#include <dlfcn.h>

static ssize_t (*real_write)(int fildes, const void *buf, size_t nbyte);
static int (*real_puts)(const char *s);

ssize_t write(int fildes, const void *buf, size_t nbyte){
    ssize_t ret;

    real_write = dlsym(RTLD_NEXT, "write");
    ret = real_write(fildes, buf, nbyte);

    fprintf(stderr, "write: %d, %s, %u => %d\n", fildes, buf, nbyte, ret);

    return ret;
}

int puts(const char *s){
    int ret;

    real_puts = dlsym(RTLD_NEXT, "puts");
    ret = real_puts(s);

    fprintf(stderr, "puts: %s => %d\n", s, ret);

    return ret;
}
