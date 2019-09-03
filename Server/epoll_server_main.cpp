#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstdio>
#include <map>
#include <vector>
#include "../utils/chat_proto.cpp"
#include "mysql_helper.h"
#include "sys/epoll.h"
#include "unrepeatId.h"

using namespace std;

#define MAX_EVENTS 1024
#define PORT 8888
#define BUFLEN 1024

class Myevent {
public:
    int fd;
    int events;
    void *args;  //指向自己
    void (*call_back)(int fd, int event, void *args);
    int status;
    char buf[BUFLEN];
    long last_active;
};

int g_efd;
Myevent g_myevents[MAX_EVENTS + 1];

void eventset(Myevent *myevent, int fd, void (*call_back)(int, int, void *),
              void *args) {
    myevent->fd = fd;
    myevent->call_back = call_back;
    myevent->args = args;
    myevent->status = 0;
    myevent->last_active = time(NULL);
    return;
}
void eventadd(int efd, int events, Myevent *pMyevent) {
    struct epoll_event epv = {0, {0}};
    int op;
    epv.data.ptr = pMyevent;
    epv.events = pMyevent->events = events;

    if (pMyevent->status == 1) {
        // 在树上
        op = EPOLL_CTL_MOD;
    } else {
        op = EPOLL_CTL_ADD;
        pMyevent->status = 1;
    }

    if (epoll_ctl(efd, op, pMyevent->fd, &epv) < 0) {
        printf("failed\n");
    } else {
        printf("event add ok");
    }
    return;
}
void accept_conn(int listen_sockfd, int events, void *args) {
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int client_sockfd;
    if ((client_sockfd = accept(listen_sockfd, (struct sockaddr *)&client_addr,
                                &len) == -1)) {
        return;
    }

    int i;
    do {
        for (i = 0; i < MAX_EVENTS; i++) {
            if (g_myevents[i].status == 0)
                break;
        }

        if (i == MAX_EVENTS)
            break;
    } while (0);
}

void init_listen_socket(int efd, short port) {
    int listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);

    memset(&server_addr, 0, server_addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(port);

    if (1 != inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)) {
        perror("Invalid IP");
        exit(1);
    }
    int listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    eventset(&g_myevents[MAX_EVENTS], listen_sockfd, accept_conn,
             &g_myevents[MAX_EVENTS]);
    eventadd(efd, EPOLLIN, &g_myevents[MAX_EVENTS]);

    // 端口复用
    int opt = 1;
    // sockfd为需要端口复用的套接字
    setsockopt(listen_sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt,
               sizeof(opt));

    if (bind(listen_sockfd, (const sockaddr *)&server_addr, server_addr_len) ==
        -1) {
        perror("Bind error");
        printf("Server bind port: %d failed!\n", port);
        exit(1);
    }

    listen(listen_sockfd, 10);
    printf("Start listening...\n");
    return;
}

int main(int argc, char const *argv[]) {
    g_efd = epoll_create(MAX_EVENTS + 1);
    if (g_efd <= 0) {
        printf("create g_efd in %s err %s\n", __func__, strerror(errno));
    }

    init_listen_socket(g_efd, PORT);

    struct epoll_event events[MAX_EVENTS + 1];

    while (1) {
        // TIMEOUT
        int nfd = epoll_wait(g_efd, events, MAX_EVENTS + 1, -1);
        if (nfd < 0) {
            printf("epoll wait error\n");
            break;
        }

        for (int i = 0; i < nfd; i++) {
            Myevent *pMyevent = (Myevent *)events[i].data.ptr;

            if ((events[i].events & EPOLLIN) && (pMyevent->events & EPOLLIN)) {
                pMyevent->call_back(pMyevent->fd, events[i].events, pMyevent->args);
            }
        }
    }
    return 0;
}
