all: queue stack

queue: queue.o
	$(CC) -o $@ $^

stack: stack.o
	$(CC) -o $@ $^

queue.o: QueAndStk.c
	$(CC) -W -Wall -DUSE_QUEUE -o $@ -c $^

stack.o: QueAndStk.c
	$(CC) -W -Wall -DUSE_STACK -o $@ -c $^

.PHONY: clean
clean:
	$(RM) queue queue.o stack stack.o
