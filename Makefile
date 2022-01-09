all: server client
CC=gcc
CFLAGS=-I.
DEPS = database.h util.h
SOBJ = server.o database.o util.o
COBJ = client.o util.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(SOBJ)
	$(CC) -o $@ $^ -lpthread -lsqlite3 $(CFLAGS)

client: $(COBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf ${SOBJ} ${COBJ}
	rm -rf client server