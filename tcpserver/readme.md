Socket server for Orange Pi
===

Developed to bind several ESP8266 to one Orange Pi as server
Uses linux sockets (see RU doc here: https://rsdn.org/article/unix/sockets.xml)
Uses SQLite DB to store connections (EN doc here: https://www.sqlite.org/cintro.html)

Installation and usage
---

```
#install sqlite and boost
sudo apt-get install sqlite3 libsqlite3-dev 
sudo apt-get install libboost-all-dev
#clone repo from git
mkdir -p /var/iot/src/
cd /var/iot/src/
git clone https://github.com/evergreen-it-dev/orangepi.git
cd /var/iot/src/orangepi/tcpserver/
mkdir -p /var/iot/tcpserver
#make
make all
#goto work dir
cd /var/iot/tcpserver/
```

Then you can run server and client

```
.\server
```
client should run as separate process (it is only test client! replace it with your own!)
```
.\client
```

To check you db manually use

```
sqlite3 iot.db
```
in sqlite use following syntax to test
sqlite> SELECT * FROM Connections;



