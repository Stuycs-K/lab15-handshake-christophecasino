.PHONY: client server
compile: client_compile server_compile
client_compile: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o

server_compile: forking_server.o pipe_networking.o
	gcc -o server forking_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

forking_server.o: forking_server.c pipe_networking.h
	gcc -c forking_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

client:
	@./client

server:
	@./server

clean:
	rm -f *.o
	rm -f *~
