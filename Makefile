CC=gcc
CFLAGS=-g -Wall -pthread
DEPS = extras.h bookorder.h queue.h hashtable.h
OBJ = main.c extras.c bookorder.c queue.c hashtable.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bookorder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
ht_test: ht_test.c hashtable.c
	$(CC) -o $@ $^ $(CFLAGS)
	
hashtable_test: hashtable_test.c hashtable.c
	$(CC) -o $@ $^ $(CFLAGS)
	
queue_test: queue_test.c hashtable.c
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm -f $(ODIR)/*.o *~ bookorder $(INCDIR)/*~ 
