CC = gcc
CFLAGS = -g -Iinclude
objects = build/main.o build/response.o
exec = server

${exec}: ${objects}
	${CC} ${CFLAGS} $^ -o $@  

${objects}: build/%.o: src/%.c
	mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	rm -rf build/ server
