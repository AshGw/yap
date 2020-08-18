#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define MAX_CONNECTIONS 10
#define RESPONSE "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Ok this is super fast frfr!</h1></body></html>"

typedef struct sockaddr_in sockaddr_in_t;

int main() {
    int file_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (file_desc == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    sockaddr_in_t server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    int bind_err = bind(file_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_err){
        perror("Bind failed");
        exit(1);
    }
    int listen_err = listen(file_desc, MAX_CONNECTIONS);
    if (listen_err) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    close(file_desc);
    return 0;
}
