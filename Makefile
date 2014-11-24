CC=gcc
CFLAGS=-g -Wall
DEPS = extras.h bookorder.h queue.h hashtable.h
OBJ = main.c extras.c bookorder.c queue.c hashtable.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bookorder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm -f $(ODIR)/*.o *~ bookorder $(INCDIR)/*~ 
