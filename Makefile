#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atilegen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/06 18:14:32 by atilegen          #+#    #+#              #
#    Updated: 2018/06/12 16:15:33 by atilegen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = 
MLXFLAGS = -lpthread -lmlx -framework OpenGL -framework AppKit
NAME = RT
HEADERS = 	includes/vectors.h \
			includes/rtv1.h
SRC =	srcs/main.c \
		srcs/helpers.c \
		srcs/img.c \
		srcs/inits.c \
		srcs/inters.c \
		srcs/parse.c \
		srcs/parse2.c \
		srcs/raytrace.c \
		srcs/vector_opers.c \
		srcs/exit.c \
		srcs/rotations.c

OBJ = $(SRC:.c=.o)
LIBFTFLAGS = -L./libft -lft
LIBFT = libft 

all: $(NAME)

%.o.c:
	@$(CC) -c $(subst .o,.c, $@) -I./libft $(CFLAGS) -o $@ 

$(NAME): $(OBJ) $(HEADERS)
	@make -C ./libft
	@$(CC) $(OBJ) -I./libft $(LIBFTFLAGS) $(MLXFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY: re clean fclean all libft