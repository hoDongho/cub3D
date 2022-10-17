# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 15:49:02 by yehyun            #+#    #+#              #
#    Updated: 2022/10/13 14:12:19 by yehyun           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
FRAMEWORK = -framework OpenGL -framework AppKit
RM = rm -f

MLXDIR = mlx/
LIBDIR = libft/
SRC_DIR = srcs/

SRC =	main.c parser.c utils.c parser_utils.c doubly_list.c map.c door.c \
		game.c key.c ray_casting.c ray_utils.c minimap.c move.c sprite.c \
		sprite_utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

HEADER = srcs/cub3d.h srcs/ray_casting.h srcs/sprite.h

ifdef DFLAG
	CFLAGS += -g2 -fsanitize=address
endif

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(MLXDIR)
	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) -Imlx/ -L$(MLXDIR) -lmlx -L$(LIBDIR) -lft $(FRAMEWORK) $^ -o $@

debug:
	@make fclean
	@make DFLAG=1 all

%.o : %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean :
	@make clean -C $(MLXDIR)
	@make clean -C $(LIBDIR)
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean :
	@make clean -C $(MLXDIR)
	@make fclean -C $(LIBDIR)
	@$(RM) $(OBJS) $(OBJS_BONUS) $(NAME)

re :
	@make fclean
	@make all

bonus : all

$(OBJS) : $(HEADER)

.PHONY : all bonus clean fclean re
