##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile MyTeams
##

NAME_SERVER = myteams_server

NAME_CLIENT = myteams_cli

FLAGS = -L./libs/myteams -lmyteams -I./include -Wall -Wextra -g3 -luuid

SRC_SERVER =    src/server/*.c \
				src/utils/*.c \
				src/server/commands/*c

SRC_CLIENT =    src/client/*.c \
				src/utils/*.c \
				src/client/handle_data/*c \
				src/client/commands/*c

all:
	gcc -o $(NAME_SERVER) $(SRC_SERVER) $(FLAGS)
	gcc -o $(NAME_CLIENT) $(SRC_CLIENT) $(FLAGS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)
	rm -rf ./BDD

re:	fclean all
