/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:13:17 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 16:17:50 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ERROR -1

# define C_OPEN 10
# define C_CLOSE 11

# define PRESS 2
# define RELEASE 3

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_M 46
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define KEY_SPACE 49
# define RED_BUTTON 17

# define W_WIDTH 1600
# define W_HEIGHT 900
# define P_WIDTH 64
# define P_HEIGHT 64
# define MOVE_SPEED 0.035
# define ROTATE_SPEED 0.03

# define MM_SIZE 25

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "ray_casting.h"

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_dlist
{
	struct s_dlist	*next;
	struct s_dlist	*prev;
	char			*line;
	int				width;
	int				height;
}					t_dlist;

typedef struct s_info
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	p_x;
	double	p_y;
	int		start_dir;
	int		map_sw;
	void	*mlx;
	void	*win;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*ceiling_color;
	t_dlist	*map;
	int		**texture;
	int		**buff;
	int		key_flag[6];
	int		ZBuffer[W_WIDTH];
	int		frame_cnt;
	t_img	main;
}			t_info;

// utils.c
int		puterr_msg(char *str);
int		free_info(t_info *info);
char	*gnl_scan(int fd, int flag);
int		set_color(char *str);

// parser_utils.c
int		ft_access(char *filename, int flag);
void	cali_info(t_info *info);
int		check_rgb(char *rgb, int i, int ret);

// doubly_list.c
t_dlist	*create_list(void);
void	add_list(t_dlist **list, char *line, int height);
void	delete_dlist(t_dlist *list);
int		find_target(t_dlist *list, int x, int y);

// parser.c
int		parsing_map(t_info *info, char *filename);

// map.c
int		check_and_make_map(t_info *info, int fd);

// game.c
int		into_game(t_info *info);
int		main_loop(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);

// key.c
int		key_press(int keycode, t_info *info);
int		key_release(int keycode, t_info *info);
int		exit_hook(t_info *info);
void	rotate_view(int keycode, t_info *info, double rotate);

// move.c
void	move_front(t_info *info);
void	move_back(t_info *info);
void	move_right(t_info *info);
void	move_left(t_info *info);

// draw.c
void	draw_cell_floor(t_info *info, t_img *img);
void	draw_game(t_info *info);

//ray_casting.c
int		ray_casting(t_info *info);
void	init_draw(t_info *info, t_ray *ray, t_draw *draw);

//ray_utils.c
void	set_info_dir(t_info *info);
void	init_ray(t_info *info, t_ray *ray, int x);
void	init_step(t_info *info, t_ray *ray);

//minimap.c
int		minimap(t_info *info);

//door.c
int		move_door(t_info *info);
int		check_door(t_dlist *now, int i);
// int		draw_door_to_img(t_info *info, t_ray *ray, t_draw *draw, int x);

//sprite.c
int		sprite_ray_casting(t_info *info);

#endif
