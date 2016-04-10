#define _GNU_SOURCE
// RTLD_NEXT is only supported in _GNU_SOURCE.
// _GNU_SOURCE should be at start of file. 
// I guess the reason is that it should be before first time including <feature.h>
// doesn't declare __USE_GNU by ourselves.

#include <stdio.h>
#include <stdarg.h>

#include <unistd.h>
#include <dlfcn.h>

#define LOG_FILE_NAME "wrapper.log"
static FILE* log_file = NULL;

static int (*real_open)(const char *path, int oflag, ...);
static FILE* (*real_fopen)(const char *path, const char *mode);
static ssize_t (*real_read)(int fildes, void *buf, size_t nbyte);
static ssize_t (*real_write)(int fildes, const void *buf, size_t nbyte);
static size_t (*real_fwrite)(const void *ptr, size_t size, size_t nmemb, FILE *stream);
static int (*real_close)(int fildes);
static int (*real_fclose)(FILE* stream);

int open(const char *path, int oflag, ...){
    if(!log_file){
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        log_file = real_fopen(LOG_FILE_NAME, "w");
    }

    int ret;

    real_open = dlsym(RTLD_NEXT, "open");
    ret = real_open(path, oflag);

    fprintf(log_file, "open[%s, %d] = %d\n", path, oflag, ret);

    return ret;
}

FILE* fopen(const char *path, const char *mode){
    if(!log_file){
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        log_file = real_fopen(LOG_FILE_NAME, "w");
    }

    FILE* ret;

    real_fopen = dlsym(RTLD_NEXT, "fopen");
    ret = real_fopen(path, mode);

    fprintf(log_file, "fopen[%s, %s] = %x\n", path, mode, ret);

    return ret;
}

ssize_t read(int fildes, void *buf, size_t nbyte){
    if(!log_file){
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        log_file = real_fopen(LOG_FILE_NAME, "w");
    }

    ssize_t ret;

    real_read = dlsym(RTLD_NEXT, "read");
    ret = real_read(fildes, buf, nbyte);

    fprintf(log_file, "read[%d, %.30s, %lu] = %d\n", fildes, buf, nbyte, ret);

    return ret;
}

ssize_t write(int fildes, const void *buf, size_t nbyte){
    if(!log_file){
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        log_file = real_fopen(LOG_FILE_NAME, "w");
    }

    ssize_t ret;

    real_write = dlsym(RTLD_NEXT, "write");
    ret = real_write(fildes, buf, nbyte);

    fprintf(log_file, "write[%d, %.30s, %lu] = %d\n", fildes, buf, nbyte, ret);

    return ret;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream){
    if(!log_file){
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        log_file = real_fopen(LOG_FILE_NAME, "w");
    }

    size_t ret;

    real_fwrite = dlsym(RTLD_NEXT, "fwrite");
    ret = real_fwrite(ptr, size, nmemb, stream);

    fprintf(log_file, "fwrite[%.30s, %lu, %lu, %x] = %lu\n", ptr, size, nmemb, stream, ret);

    return ret;
}

int close(int fildes){
    if(!log_file){
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        log_file = real_fopen(LOG_FILE_NAME, "w");
    }

    int ret;

    real_close = dlsym(RTLD_NEXT, "close");
    ret = real_close(fildes);

    fprintf(log_file, "close[%d] = %d\n", fildes, ret);

    return ret;
}

int fclose(FILE* stream){
    if(!log_file){
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        log_file = real_fopen(LOG_FILE_NAME, "w");
    }

    int ret;

    real_fclose = dlsym(RTLD_NEXT, "fclose");
    ret = real_fclose(stream);

    fprintf(log_file, "fclose[%x] = %d\n", stream, ret);

    return ret;
}
