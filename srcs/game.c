/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: littley <littley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:08:00 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 00:33:51 by littley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(info->mlx, path,
			&img->width, &img->height);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			texture[img->width * y + x] = img->addr[img->width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	set_info(t_info *info)
{
	int		i;
	int		j;
	t_img	img;

	i = -1;
	info->buff = ft_calloc(W_HEIGHT, sizeof(int *));
	while (++i < W_HEIGHT)
		info->buff[i] = ft_calloc(W_WIDTH, sizeof(int));
	j = -1;
	info->texture = ft_calloc(5, sizeof(int *));
	while (++j < 5)
		info->texture[j] = ft_calloc(P_HEIGHT * P_WIDTH, sizeof(int));
	load_image(info, info->texture[0], info->ea_path, &img);
	load_image(info, info->texture[1], info->we_path, &img);
	load_image(info, info->texture[2], info->so_path, &img);
	load_image(info, info->texture[3], info->no_path, &img);
	load_image(info, info->texture[4], "imgs/DOOR_2A.xpm", &img);
}

int	mouse_move(t_info *info)
{
	const int	std_x = W_WIDTH / 2;
	int			x;
	int			y;

	mlx_mouse_get_pos(info->mlx, info->win, &x, &y);
	if (y < 0 || y > W_HEIGHT)
		return (0);
	if (x > std_x + W_WIDTH / 4)
		rotate_view(KEY_RIGHT, info, ROTATE_SPEED / 500 * abs(std_x - x));
	else if (x < std_x - W_WIDTH / 4)
		rotate_view(KEY_LEFT, info, ROTATE_SPEED / 500 * abs(std_x - x));
	return (0);
}

int	main_loop(t_info *info)
{
	draw_cell_floor(info, &info->main);
	ray_casting(info);
	draw_game(info);
	mouse_move(info);
	if (info->key_flag[0])
		move_front(info);
	if (info->key_flag[1])
		move_back(info);
	if (info->key_flag[2])
		move_right(info);
	if (info->key_flag[3])
		move_left(info);
	if (info->key_flag[4])
		rotate_view(KEY_LEFT, info, ROTATE_SPEED);
	if (info->key_flag[5])
		rotate_view(KEY_RIGHT, info, ROTATE_SPEED);
	if (info->map_sw)
		minimap(info);
	return (0);
}

int	into_game(t_info *info)
{
	info->mlx = mlx_init();
	mlx_do_key_autorepeatoff(info->mlx);
	set_info(info);
	set_info_dir(info);
	info->win = mlx_new_window(info->mlx,
			W_WIDTH, W_HEIGHT, "cub3d");
	info->main.img = mlx_new_image(info->mlx,
			W_WIDTH, W_HEIGHT);
	info->main.addr = (int *)mlx_get_data_addr(info->main.img, &info->main.bpp,
			&info->main.line_length, &info->main.endian);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, PRESS, 1L << 0, &key_press, info);
	mlx_hook(info->win, RELEASE, 1L << 1, &key_release, info);
	mlx_hook(info->win, 33, 1L << 17, &exit_hook, info);
	mlx_loop(info->mlx);
	return (0);
}
