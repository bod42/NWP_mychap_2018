/*
** EPITECH PROJECT, 2019
** client
** File description:
** client
*/

#include <sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<netinet/udp.h>
#include<netinet/ip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct pseudo_header
{
	u_int32_t source_address;
	u_int32_t dest_address;
	u_int8_t placeholder;
	u_int8_t protocol;
	u_int16_t udp_length;
};

typedef struct client {
    int ac;
    char **av;
    int flag;
    int psize;
    char **tab;
    char datagram[4096];
    char source_ip[32];
    char *data;
    char *pseudogram;
    char *buff;
	struct sockaddr_in sin;
	struct pseudo_header psh;
}client_t;

char **my_strtowordtab(char *);
void send_message(client_t *cli);
void recev(client_t *cli, int);
