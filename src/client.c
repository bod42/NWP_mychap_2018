/*
** EPITECH PROJECT, 2019
** client
** File description:
** client
*/

#include "client.h"

int client(client_t *cli)
{
    struct option long_options[] = {
        {"target", required_argument, NULL, '1'},
        {"port", required_argument, NULL, '2'},
        {"password", required_argument, NULL, '3'},
        {NULL, 0, NULL, 0}
    };
    int option_index = 0;
    int i = 0;

    while (cli->flag != -1) {
        cli->flag = getopt_long(cli->ac, cli->av, "t:,p:,P:,1:,2:,3:",
                                long_options, &option_index);
        cli->tab[i] = optarg;
        i++;
    }
    send_message(cli);
    return (0);
}

void malloc_tab(client_t *cli)
{
    int i = 0;

    cli->tab = malloc(255);
    while (cli->tab[i]) {
        cli->tab[i] = malloc(255);
        i++;
    }
}

void init_struct(client_t *cli, int ac, char **av)
{
    cli->ac = ac;
    cli->av = av;
    cli->buff = NULL;
    cli->flag = 0;
    cli->pseudogram = NULL;
    malloc_tab(cli);
}

int main(int ac, char **av)
{
    client_t *cli = malloc(sizeof(client_t) + 1);

    if (ac < 7 || ac > 7)
        return (84);
    init_struct(cli, ac, av);
    client(cli);
    return (0);
}
