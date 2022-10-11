# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 15:49:02 by yehyun            #+#    #+#              #
#    Updated: 2022/10/11 16:42:54 by yehyun           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAME_BONUS = cub3d_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAG = -g2 -fsanitize=address
FRAMEWORK = -framework OpenGL -framework AppKit
RM = rm -f

MLXDIR = mlx/
LIBDIR = libft/
SRC_DIR = srcs/

SRC =	main.c parser.c utils.c parser_utils.c doubly_list.c map.c door.c \
		game.c key.c ray_casting.c ray_utils.c minimap.c move.c draw.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

HEADER = srcs/cub3d.h

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(MLXDIR)
	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) -Imlx/ -L$(MLXDIR) -lmlx -L$(LIBDIR) -lft $(FRAMEWORK) $^ -o $@

%.o : %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean :
	@make clean -C $(MLXDIR)
	@make clean -C $(LIBDIR)
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean :
	@make clean -C $(MLXDIR)
	@make fclean -C $(LIBDIR)
	@$(RM) $(OBJS) $(OBJS_BONUS) $(NAME) $(NAME_BONUS)

re :
	@make fclean
	@make all

bonus : $(NAME_BONUS)

$(OBJS) : $(HEADER)

$(NAME_BONUS) : $(OBJS_BONUS)
	@make -C $(MLXDIR)
	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) -L$(MLXDIR) -lmlx -L$(LIBDIR) -lft $(FRAMEWORK) $^ -o $@

.PHONY : all bonus clean fclean re