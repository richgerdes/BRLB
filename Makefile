CC=gcc
CFLAGS=-g -Wall
DEPS = queue.h hashtable.h
OBJ = hashtable_test.c queue.c hashtable.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bookorder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm -f $(ODIR)/*.o *~ bookorder $(INCDIR)/*~ 
