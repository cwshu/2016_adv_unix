CC = clang
CFLAGS = -std=gnu99 -Wall -g

EXE = main
OBJS = main.o job.o

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
