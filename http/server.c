#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6969
#define MAX_CONNECTIONS 10
#define RESPONSE_200 "HTTP/1.1 200 OK\n"\
                      "Content-Type: text/html\n\n"\
                      "<html><body><h1>Ok this is super fast frfr!</h1></body></html>"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\n"\
                      "Content-Type: text/html\n\n"\
                      "<html><body><h1>404 Not Found</h1></body></html>"

typedef struct sockaddr_in sockaddr_in_t;

void handle_request(int new_socket_desc) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_received = recv(new_socket_desc, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1) {
        perror("reading failed");
        return;
    }

    if (strstr(buffer, "GET / HTTP/1.1") != NULL) {
        send(new_socket_desc, RESPONSE_200, strlen(RESPONSE_200), 0);
    } else {
        send(new_socket_desc, RESPONSE_404, strlen(RESPONSE_404), 0);
    }
    close(new_socket_desc);
}


int main() {
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        perror("socket creation failed");
        exit(-1);
    }

    sockaddr_in_t server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    int bind_err = bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_err) {
        perror("binding failed");
        exit(-1);
    }

    int listen_err = listen(socket_desc, MAX_CONNECTIONS);
    if (listen_err) {
        perror("listening failed");
        exit(-1);
    }

    printf("server listening on http://localhost:%d\n", PORT);
    sockaddr_in_t client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        int new_socket_desc = accept(socket_desc, (struct sockaddr *)&client_addr, &addr_len);
        if (new_socket_desc == -1) {
            perror("accept failed");
            continue;
        }

        printf("connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        handle_request(new_socket_desc);
    }

    close(socket_desc);
    return 0;
}
