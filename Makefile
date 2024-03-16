# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 16:18:18 by mimoreir          #+#    #+#              #
#    Updated: 2023/04/25 16:18:18 by mimoreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	so_long

LIBFT	=	libft/libft.a

MINILIBX	=	minilibx-linux/libmlx.a

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -f
AR		=	ar rcs

SOURCES_FILES	=	main.c validate_map.c validate_map2.c free_game.c validate_path.c \
					so_long.c handle_event.c\

HEADER	=	so_long.h

OBJECTS			= 	$(SOURCES_FILES:.c=.o)

MLXFLAGS		=	-L  -lmlx -Ilmlx -lXext -lX11

.c.o:
		$(CC) $(CFLAGS) -c $< -g -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(LIBFT) $(MINILIBX) $(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
			$(MAKE) -C ./libft

$(MINILIBX):
			$(MAKE) -C ./minilibx-linux

clean:
				$(MAKE) -C ./libft clean
				$(MAKE) -C ./minilibx-linux clean
				$(RM) $(OBJECTS) $(OBJECTS_BONUS)

fclean:			clean
				$(MAKE) -C ./libft fclean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean all
