#include "homa.h"

#include<stdio.h>
#include <errno.h>
#include <execinfo.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#define MSGLEN 1024

int main()
{
    int fd;
    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_HOMA);
    if (fd < 0) {
        printf("Create homa socket failed");
        return -1;
    }

    int port = 12345;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    char msg[HOMA_MAX_MESSAGE_LENGTH];
    char buf[HOMA_MAX_MESSAGE_LENGTH];

    int ret, len;
    size_t addr_len = sizeof(addr);
    uint64_t rpc_id;
    
    while (1) {

        memset(msg, '0', MSGLEN);
        ret = homa_send(fd, &msg, MSGLEN,(struct sockaddr*)&addr, addr_len, &rpc_id);
        if (ret < 0) {
            printf("Homa send() failed!");
            return -1;
        }
        // printf("Homa send() succeed!\n");

        len = homa_recv(fd, buf, HOMA_MAX_MESSAGE_LENGTH,
                               HOMA_RECV_RESPONSE, (struct sockaddr *) &addr,
                               &addr_len, &rpc_id, NULL);
        if (len < 0) {
            printf("Homa recv() grants failed!\n");
            return -1;
        }
        // printf("Homa recv() succeed!\n\n");

    }

    return 0;
}
