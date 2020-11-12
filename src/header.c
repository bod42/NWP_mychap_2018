/*
** EPITECH PROJECT, 2019
** header
** File description:
** header
*/

#include "client.h"

unsigned short csum(unsigned short *ptr,int nbytes)
{
    register long sum = 0;
    unsigned short oddbyte;
    register short answer;

    while(nbytes>1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if(nbytes==1) {
        oddbyte = 0;
        *((u_char*)&oddbyte) = *(u_char*)ptr;
        sum += oddbyte;
    }
    sum = (sum >> 16) + (sum &0xffff);
    sum = sum + (sum >> 16);
    answer = (short)~sum;
    return(answer);
}

void send_message_3(client_t *cli, struct udphdr *udph)
{
    udph->source = htons (54321);
    udph->dest = htons (atoi(cli->tab[1]));
    udph->len = htons(8 + strlen(cli->data));
    udph->check = 0;
    cli->psh.source_address = inet_addr(cli->source_ip);
    cli->psh.dest_address = cli->sin.sin_addr.s_addr;
    cli->psh.placeholder = 0;
    cli->psh.protocol = IPPROTO_UDP;
    cli->psh.udp_length = htons(sizeof(struct udphdr) + strlen(cli->data) );
    cli->psize = sizeof(struct pseudo_header) +
    sizeof(struct udphdr) + strlen(cli->data);
    cli->pseudogram = malloc(cli->psize);
    memcpy(cli->pseudogram, (char*)&cli->psh, sizeof (struct pseudo_header));
    memcpy(cli->pseudogram + sizeof(struct pseudo_header), udph,
    sizeof(struct udphdr) + strlen(cli->data));
}

void send_message_2(client_t *cli, struct iphdr *iph)
{
    memset (cli->datagram, 0, 4096);
    cli->data = cli->datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(cli->data , "client hello");
    if (strcmp(cli->tab[0], "localhost") == 0)
        strcpy(cli->source_ip, "127.0.0.1");
    else
        strcpy(cli->source_ip , cli->tab[0]);
    cli->sin.sin_family = AF_INET;
    cli->sin.sin_port = htons(80);
    cli->sin.sin_addr.s_addr = inet_addr (cli->tab[0]);
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof (struct iphdr) +
    sizeof (struct udphdr) + strlen(cli->data);
    iph->id = htonl (54321);
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;
    iph->saddr = inet_addr (cli->source_ip);
    iph->daddr = cli->sin.sin_addr.s_addr;
    iph->check = csum ((unsigned short *) cli->datagram, iph->tot_len);
}

void send_message(client_t *cli)
{
    struct iphdr *iph = (struct iphdr *) cli->datagram;
    struct udphdr *udph = (struct udphdr *)
    (cli->datagram + sizeof (struct ip));
    int s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    int a;

    setsockopt(s, IPPROTO_IP, IP_HDRINCL, &a, sizeof(a));
    if(s == -1) {
        perror("Failed to create raw socket");
        exit(84);
    }
    if (strcmp(cli->tab[0], "localhost") != 0)
        if (strchr(cli->tab[0], '.') == NULL) {
            printf("No such hostname: '%s'", cli->tab[0]);
            exit (84);
        }
    send_message_2(cli, iph);
    send_message_3(cli, udph);
    udph->check = csum((unsigned short*)cli->pseudogram, cli->psize);
		if (sendto (s, cli->datagram, iph->tot_len, 0, (struct sockaddr *)
    &cli->sin, sizeof(cli->sin)) < 0) {
        perror("sendto failed");
    }
    printf("KO\n");
    //recev(cli, s);
}
