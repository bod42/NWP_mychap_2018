##
## EPITECH PROJECT, 2019
## ftp
## File description:
## ftp
##

CC	=	gcc

CPPFLAGS += -I ./include

CFLAGS += -Wall -Wextra

SRCS		=	src/client.c									\
				  src/header.c									\
					src/recv.c

OBJS	=	$(SRCS:.c=.o)

NAME =	client

all: $(NAME)

$(NAME): 	$(OBJS)
					gcc -o $(NAME) $(OBJS)

clean:
				rm -f $(OBJS)

fclean: clean
				rm -f $(NAME)

re:		fclean all

.PHONY:		ftp all re clean fclean
