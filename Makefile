# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 13:52:06 by gaguado-          #+#    #+#              #
#    Updated: 2021/11/23 17:39:17 by gaguado-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =				gcc
INCLUDES =			includes

LIBFTLOC =			libft
FLAGS =				-Wall -Wextra -Werror -I./$(INCLUDES) -I./$(LIBFTLOC)/$(INCLUDES)
SRC_DIR =			srcs
NAME =				server
NAME_CLIENT = 		client

FILENAMES_SERVER =	$(SRC_DIR)/server.c
FILENAMES_CLIENT =	$(SRC_DIR)/client.c

OBJS_SERVER	=		$(FILENAMES_SERVER:c=o)
OBJS_CLIENT	=		$(FILENAMES_CLIENT:c=o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS_SERVER) $(OBJS_CLIENT)
	$(MAKE) -C ./$(LIBFTLOC)
	$(CC) $(FLAGS) $(word 1, $^) $(LIBFTLOC)/libft.a -o $(NAME)
	$(CC) $(FLAGS) $(word 2, $^) $(LIBFTLOC)/libft.a -o $(NAME_CLIENT)

all: $(NAME)

clean:
	$(MAKE) -C ./$(LIBFTLOC) clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C ./$(LIBFTLOC) fclean
	rm -rf $(NAME)

norme:
	norminette $(SRC_DIR)/*.[ch] $(SRC_DIR)/instructions/*.[ch] $(LIBFTLOC)/srcs/*.[ch]

re: fclean all

.PHONY: all clean fclean re norme test test_checker