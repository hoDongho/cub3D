/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: littley <littley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:13:17 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/07 21:18:22 by littley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ERROR -1

# define C_OPEN 10
# define C_CLOSE 11

# define PRESS 2
# define RELEASE 3
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_M 109
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define RED_BUTTON 79
# define KEY_SPACE 32

# define P_WIDTH 64
# define P_HEIGHT 64

# define MM_SIZE 18

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <../mlx_linux/mlx.h>
# include "../libft/libft.h"

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

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
}			t_ray;

typedef struct s_draw
{
	int		line_height;
	int		start;
	int		end;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	int		color;
	double	wall_x;
	double	step;
	double	tex_pos;
}			t_draw;

typedef struct s_var
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}			t_var;

typedef struct s_info
{
	t_var	var;
	t_ray	ray;
	t_img	main;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	p_x;
	double	p_y;
	double	move_speed;
	int		start_dir;
	int		map_sw;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*ceiling_color;
	t_dlist	*map;
	int		**texture;
	int		**buff;
}			t_info;

// utils.c
int		puterr_msg(char *str);
int		free_info(t_info *info);
char	*gnl_scan(int fd, int flag);
int		set_color(char *str);

// parser_utils.c
int		ft_access(char *filename, int flag);
void	cali_info(t_info *info);
int		check_rgb(char *rgb, int i);

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

// key.c
int		key_press(int keycode, t_info *info);
int		exit_hook(t_var *var);
void	press_left_right(int keycode, t_info *info, double rotate);

// move.c
void	move_front(t_info *info);
void	move_back(t_info *info);
void	move_right(t_info *info);
void	move_left(t_info *info);

// draw.c
void	draw_cell_floor(t_info *info, t_img *img);
void	draw_game(t_info *info);

//ray_casting.c
int		ray_casting(t_info *info, t_ray *ray);

//ray_utils.c
void	set_info_dir(t_info *info);
void	init_ray(t_info *info, t_ray *ray, int x);
void	init_step(t_info *info, t_ray *ray);

//minimap.c
int		minimap(t_info *info);

#endif
