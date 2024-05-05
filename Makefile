CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEPS = interpreter.h
OBJ = main.o interpreter.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

brainfrick: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf brainfrick *.o