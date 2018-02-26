all:
	g++ server.cpp -o server -lsqlite3
	g++ client.cpp -o client

server:
	g++ server.cpp -o server -lsqlite3

client:
	g++ client.cpp -o client

clean:
	rm -rf *.o socket client server