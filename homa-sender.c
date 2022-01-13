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

#define MSGLEN 10000

int main(int argc, char *argv[])
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
    addr.sin_addr.s_addr = inet_addr("10.0.0.33");    // server's ip
    size_t addr_len = sizeof(addr);
    
    char msg[HOMA_MAX_MESSAGE_LENGTH];
    int ret;
    uint64_t rpc_id;

    memset(msg, '0', MSGLEN);
    ret = homa_send(fd, &msg, MSGLEN,(struct sockaddr*)&addr, addr_len, &rpc_id);
    if (ret < 0) {
        printf("%d Homa send() failed!", errno);
        return -1;
    }
    sleep(1);
    return 0;
}
