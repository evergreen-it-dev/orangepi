all:
	g++ server.cpp -o /var/iot/tcpserver/server -lsqlite3
	g++ client.cpp -o /var/iot/tcpserver/client

server:
	g++ server.cpp -o /var/iot/tcpserver/server -lsqlite3

client:
	g++ client.cpp -o /var/iot/tcpserver/client

clean:
	rm -rf *.o socket client server