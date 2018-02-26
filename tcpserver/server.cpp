#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sqlite3.h>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string/replace.hpp>


#define PORT 9000


template <class T>
std::string to_string(T param)
{
    std::string str = "";
    std::stringstream ss;
    ss<<param;
    std::getline(ss, str);
    return str;
}

// This is the callback function to display the select data in the table
static int callback(void *NotUsed, int argc, char **argv, char **szColName)
{
    for(int i = 0; i < argc; i++)
    {
        std::cout << szColName[i] << " = " << argv[i] << std::endl;
    }

    std::cout << "\n";

    return 0;
}

char response[] = "{\"success\":1}\n";

int main() {
    std::clock_t ts,tn;
    ts = std::clock();
    printf ("Server started\r\n");

    sqlite3 *db;
    char *zErrMsg = 0;
    char *szErrMsg = 0;
    int rc;

    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    rc = sqlite3_open("iot.db", &db);





    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");

        std::string initTableSQL = "CREATE TABLE Connections(port int(4), message varchar(30))";
        rc = sqlite3_exec(db, initTableSQL.c_str(), callback, 0, &szErrMsg);
        if(rc != SQLITE_OK) {
            int found = std::string(szErrMsg).find("already exists");
            if (found!=std::string::npos)
                std::cout << "Table exits, continue \n";
            else
                std::cout << "SQL Error: " << szErrMsg << std::endl;
            sqlite3_free(szErrMsg);
        }
    }

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("Listener not inited");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1); //1 это длина очереди на соединение сокета
    tn=std::clock()-ts;
    printf ("To start socket and DB connection: %f seconds",((float)tn)/CLOCKS_PER_SEC);

    while(1)//infinite listening
    {
            std::string insertSQL = "INSERT INTO Connections(port, message) VALUES ";
            sock = accept(listener, NULL, NULL);
            if(sock < 0)
            {
                perror("accept");
                exit(3);
            }

            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            printf("Client says: %s\r\n",buf);
            insertSQL+="("+to_string(PORT)+",'"+to_string(buf)+"')";
            insertSQL=boost::replace_all_copy( insertSQL, "\"", "\\\"");
            std::cout << insertSQL+"\r\n";

            rc = sqlite3_exec(db, insertSQL.c_str(), callback, 0, &szErrMsg);
            if(rc != SQLITE_OK)
            {
                std::cout << "SQL Error: " << szErrMsg << std::endl;
                send(sock, szErrMsg, sizeof(szErrMsg)+1, 0);
                sqlite3_free(szErrMsg);

            }else
                send(sock, response, sizeof(response)+1, 0);
            close(sock);

    }
    close (listener);
    sqlite3_close(db);

    return 0;
}


