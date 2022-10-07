/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:08:00 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/07 13:49:21 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cell_floor(t_info *info, t_img *img)
{
	int	i;
	int	j;
	int	ceiling;
	int	floor;

	ceiling = set_color(info->ceiling_color);
	floor = set_color(info->floor_color);
	i = -1;
	while (++i < info->var.height)
	{
		j = -1;
		while (++j < info->var.width)
		{
			if (i < info->var.height / 2)
				img->addr[i * info->var.width + j] = ceiling;
			if (i >= info->var.height / 2)
				img->addr[i * info->var.width + j] = floor;
		}
	}
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(info->var.mlx, path,
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
	mlx_destroy_image(info->var.mlx, img->img);
}

void	set_info(t_info *info)
{
	int		i;
	int		j;
	t_img	img;

	info->var.width = 1200;
	info->var.height = 700;
	info->move_speed = 0.2;
	info->rotate = 0.2;
	i = -1;
	info->buff = ft_calloc(info->var.height, sizeof(int *));
	while (++i < info->var.height)
		info->buff[i] = ft_calloc(info->var.width, sizeof(int));
	j = -1;
	info->texture = ft_calloc(4, sizeof(int *));
	while (++j < 4)
		info->texture[j] = ft_calloc(P_HEIGHT * P_WIDTH, sizeof(int));
	load_image(info, info->texture[0], info->ea_path, &img);
	load_image(info, info->texture[1], info->we_path, &img);
	load_image(info, info->texture[2], info->so_path, &img);
	load_image(info, info->texture[3], info->no_path, &img);
}

void	draw_game(t_info *info)
{
	int	x;
	int	y;

	y = -1;
	while (++y < info->var.height)
	{
		x = -1;
		while (++x < info->var.width)
		{
			if (info->buff[y][x])
			{
				info->main.addr[y * info->var.width + x] = info->buff[y][x];
				info->buff[y][x] = 0;
			}
		}
	}
	mlx_put_image_to_window(info->var.mlx, info->var.win, info->main.img, 0, 0);
}

int	main_loop(t_info *info)
{
	draw_cell_floor(info, &info->main);
	ray_casting(info, &info->ray);
	draw_game(info);
	return (0);
}

int	into_game(t_info *info)
{
	info->var.mlx = mlx_init();
	set_info(info);
	set_info_dir(info);
	info->var.win = mlx_new_window(info->var.mlx, info->var.width, info->var.height, "cub3d");
	info->main.img = mlx_new_image(info->var.mlx, info->var.width, info->var.height);
	info->main.addr = (int *)mlx_get_data_addr(info->main.img, &info->main.bpp,
			&info->main.line_length, &info->main.endian);
	mlx_loop_hook(info->var.mlx, &main_loop, info);
	mlx_hook(info->var.win, PRESS, 0, &key_press, info);
	mlx_hook(info->var.win, RED_BUTTON, 0, &exit_hook, &info->var);
	mlx_loop(info->var.mlx);
	return (0);
}
