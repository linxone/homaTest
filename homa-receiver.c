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
#include <pthread.h>

int main()
{
    int fd;
    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_HOMA);
    if (fd < 0) {
        printf("Create homa socket failed!");
        return -1;
    }

    int port = 12345;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    if ( bind(fd, (struct sockaddr *)&addr, sizeof(addr)) != 0 ) {
        printf(" Bind() failed! ");
        return -1;
    }

    char buf[HOMA_MAX_MESSAGE_LENGTH];
    struct sockaddr_in src;
    size_t src_len = sizeof(src);
    int len;

    while (1) {
        
        uint64_t id = 0;
        len = homa_recv(fd, buf, HOMA_MAX_MESSAGE_LENGTH, HOMA_RECV_REQUEST, 
                    (struct sockaddr *)&src, &src_len, &id, NULL);
        if (len < 0) {
            printf("Homa recv() failed!\n");
            return -1;
        }
        printf("SERVER: %d\n", len);
    }

    return 0;
}
