# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nvan-win <nvan-win@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/11 10:50:57 by nvan-win      #+#    #+#                  #
#    Updated: 2022/02/11 11:43:44 by nvan-win      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h
INC_DIR = ./includes/
SRC_DIR = ./src/
OBJ_DIR = ./obj/
CFLAGS = -Wall -Wextra -Werror
OBJ_FILES =		$(OBJ_DIR)cleanup.o \
				$(OBJ_DIR)main.o \
				$(OBJ_DIR)monitor.o \
				$(OBJ_DIR)philo_utils.o \
				$(OBJ_DIR)simulation.o \
				$(OBJ_DIR)start.o \
				$(OBJ_DIR)time.o \

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)$(HEADER)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
