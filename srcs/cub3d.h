/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:13:17 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/05 10:44:02 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ERROR -1

# define C_OPEN 10
# define C_CLOSE 11

# define PRESS 2
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define RED_BUTTON 17

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "../libft/libft.h"

typedef struct s_dlist
{
	struct s_dlist	*next;
	struct s_dlist	*prev;
	char			*line;
	int				width;
	int				height;
}					t_dlist;

typedef struct s_var
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}				t_var;

typedef struct s_info
{
	int		p_x;
	int		p_y;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*ceiling_color;
	t_dlist	*map;
}	t_info;

// utils.c
int		puterr_msg(char *str);
int		parsing_map(t_info *info, char *filename);
int		free_info(t_info *info);
char	*gnl_scan(int fd, int flag);

// parser_utils.c
int		ft_access(char *filename, int flag);
void	cali_info(t_info *info);
int		check_rgb(char *rgb, int i);

// doubly_list.c
t_dlist	*create_list(void);
void	add_list(t_dlist **list, char *line, int height);
void	delete_dlist(t_dlist *list);

// map.c
int		check_and_make_map(t_info *info, int fd);

// game.c
int		into_game(t_info *info);

// key.c
int		key_press(int keycode, t_var *var);
int		exit_hook(t_var *var);

#endif
