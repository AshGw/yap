#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define MAX_CONNECTIONS 10
#define RESPONSE "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Ok this is super fast frfr!</h1></body></html>"

int main() {
    int file_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (file_desc == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    close(file_desc);
    return 0;
}
