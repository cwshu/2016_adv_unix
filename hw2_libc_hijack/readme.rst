Advanced Programming in the UNIX Environment HW2
================================================

libc hijacking experiment
-------------------------

The finish part is retrieving file infomation of ``wget`` program. 
More clearly, retrieving ``open/close/read/write`` dependent libc call with parameter and return value.

build and testing
~~~~~~~~~~~~~~~~~

1. build code::
   
    make all # hijacking library is at bin/libwrapper.so

2. testing::

    # bash shell syntax
    LD_PRELOAD=./bin/libwrapper.so wget "www.google.com"
    # infomation is at wrapper.log

We can compare ``wrapper.log`` to ``ltrace``'s log.
::

    ltrace -o ltrace.log wget "www.google.com"
    grep ltrace.log -e "open\|close\|read\|write" > ltrace.file.log
    # compare wrapper.log to ltrace.file.log

detail
~~~~~~

wrapping function::
    
    int open(const char *path, int oflag, ...); // int mode
    FILE *fopen(const char *path, const char *mode);

    ssize_t read(int fildes, void *buf, size_t nbyte);
    ssize_t write(int fildes, const void *buf, size_t nbyte);
    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

    int close(int fildes);
    int fclose(FILE *stream);



