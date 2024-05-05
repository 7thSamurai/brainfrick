CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEPS = 
OBJ = main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

brainfrick: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf brainfrick *.o