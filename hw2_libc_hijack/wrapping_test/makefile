CC = gcc
CFLAGS = -Wall

all: output libwrapper.so

libwrapper.so: wrapper.c
	$(CC) -fPIC -shared -o $@ $< -ldl

output: output.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.so *.o output
