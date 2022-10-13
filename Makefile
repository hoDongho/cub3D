# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: littley <littley@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 15:49:02 by yehyun            #+#    #+#              #
#    Updated: 2022/10/13 20:27:58 by littley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc -O2
CFLAGS = -Wall -Wextra -Werror
DFLAG = -g2 -fsanitize=address
RM = rm -f

LIBDIR = libft/
SRC_DIR = srcs/

SRC =	main.c parser.c utils.c parser_utils.c doubly_list.c map.c door.c \
		game.c key.c ray_casting.c ray_utils.c minimap.c move.c draw.c sprite.c \
		sprite_utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

HEADER = srcs/cub3d.h

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(LIBDIR)
	@$(CC) $^ $(CFLAGS) -lmlx -L$(LIBDIR) -lft -lXext -lX11 -lm -lz -o $@

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make clean -C $(LIBDIR)
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean :
	@make fclean -C $(LIBDIR)
	@$(RM) $(OBJS) $(OBJS_BONUS) $(NAME) $(NAME_BONUS)

re :
	@make fclean
	@make all

bonus :
	@make all

.PHONY : all bonus clean fclean re