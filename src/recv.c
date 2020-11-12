/*
** EPITECH PROJECT, 2019
** recv
** File description:
** recv
*/

#include "client.h"

void recev(client_t *cli, int s)
{
    char Buffer[1024];
    struct sockaddr udpaddrfrom;
    unsigned int fromlen = sizeof(udpaddrfrom);
    int cbRead;

    cli->sin.sin_family = AF_INET ;
    cli->sin.sin_addr.s_addr = htonl (INADDR_ANY);
    cli->sin.sin_port = htons((unsigned short)atoi(cli->tab[1]));
    bind(s, (struct sockaddr *)&cli->sin, sizeof(cli->sin));
    cbRead = recvfrom(s, Buffer, sizeof(Buffer), 0, &udpaddrfrom, &fromlen);
    if(cbRead <= 0) {
        exit (-1);
    }
    Buffer[cbRead] = 0;
    printf("recvfrom()=>cbRead=%d, Buffer=%s\n", cbRead, Buffer);
}
