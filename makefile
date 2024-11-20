# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 07:10:51 by bde-wits          #+#    #+#              #
#    Updated: 2024/11/20 10:42:11 by bde-wits         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c\
			ft_calloc.c\
			ft_split.c\
			get_next_line_utils.c\
			get_next_line.c\
			
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lmlx -lXext -lX11 -L minilibx-linux
NAME = Cub3D

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re