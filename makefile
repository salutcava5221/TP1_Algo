CFLAGS = -std=c11 -O2 -Wall -Wextra -finput-charset=UTF-8 -fexec-charset=UTF-8

all: app
app : main.o node.o
	gcc $(CFLAGS) main.o node.o -o app

node.o : node.c node.h
	gcc $(CFLAGS) -c node.c -o node.o

main.o : main.c node.h
	gcc $(CFLAGS) -c main.c -o main.o

clean:
	del /Q main.o node.o app.exe app
