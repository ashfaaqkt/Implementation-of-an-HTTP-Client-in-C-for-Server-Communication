#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "80"
#define BUFFER_SIZE 4096

int create_socket_and_connect(const char *hostname) {
    struct addrinfo hints, *res, *p;
    int sockfd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, PORT, &hints, &res) != 0) {
        perror("getaddrinfo");
        exit(1);
    }

    for (p = res; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) continue;

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "Failed to connect to %s\n", hostname);
        exit(2);
    }

    freeaddrinfo(res);
    return sockfd;
}

void send_http_get_request(int sockfd, const char *hostname, const char *path) {
    char request[1024];

    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n\r\n",
             path, hostname);

    if (send(sockfd, request, strlen(request), 0) == -1) {
        perror("send");
        exit(3);
    }

    printf("HTTP GET request sent to %s\n\n", hostname);
}

void receive_http_response(int sockfd) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    if (bytes_received < 0) {
        perror("recv");
    }
}

void interact_with_server(const char *hostname, const char *path) {
    printf("Interacting with server %s...\n\n", hostname);

    int sockfd = create_socket_and_connect(hostname);
    send_http_get_request(sockfd, hostname, path);
    receive_http_response(sockfd);
    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <hostname> [path]\n", argv[0]);
        exit(1);
    }

    const char *hostname = argv[1];
    const char *path = (argc >= 3) ? argv[2] : "/";

    interact_with_server(hostname, path);
    return 0;
}

