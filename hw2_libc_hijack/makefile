CC = gcc
CFLAGS = -std=gnu99

all: bin/libwrapper.so

bin/libwrapper.so: src/wrapper.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $< -ldl

clean:
	rm -f bin/*.so

