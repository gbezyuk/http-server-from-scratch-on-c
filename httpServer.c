#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define LISTENING_MODE 10

#define true 1
#define false 0
#define fileDescriptor int
#define internetAddress struct sockaddr_in

#include "httpServerUtils.c"

int main (int argc, char const *argv[]) {
    fileDescriptor server;
    internetAddress address;
    size_t addrlen = sizeof(address);

    server = createServerSocket();
    initLocalhostAddress(&address);
    bindServerToLocalhostAddress(server, &address);
    startListening(server);

    while (true) {
        printf("\n+++++++ Waiting for new requests ++++++++\n\n");
        fileDescriptor connection = acceptNewInternetConnection(server, &address, &addrlen);

        char buffer[30000] = {0};
        long valread;
        valread = read(connection, buffer, 30000);
        printf("%ld bytes or incoming request read:\n\n%s\n", valread, buffer);

        const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
        write(connection, response, strlen(response));
        printf("\n------------------Response sent-------------------\n");

        close(connection);
    }
    return 0;
}
