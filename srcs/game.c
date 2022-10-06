/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:08:00 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/05 17:03:45 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cell_floor(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1080)
	{
		j = 0;
		while (j < 1920)
		{
			if (i < 540)
				mlx_pixel_put(info->var.mlx, info->var.win, j, i, \
				set_color(info->ceiling_color));
			if (i >= 540)
				mlx_pixel_put(info->var.mlx, info->var.win, j, i, \
				set_color(info->floor_color));
			j++;
		}
		i++;
	}
}

int	dda(t_info *info, double rayDirX, double rayDirY, int start_x)
{
	int		mapX, mapY, stepX, stepY, side, hit;
	double	sideDistX, sideDistY, deltaDistX, deltaDistY, perpWallDist;

	mapX = (int)info->p_x;
	mapY = (int)info->p_y;
	hit = 0;
	deltaDistX = fabs((double)1 / rayDirX);
	deltaDistY = fabs((double)1 / rayDirY);
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (info->p_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (1.0 - info->p_x + mapX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = 1;
		sideDistY = (info->p_y - mapY) * deltaDistY;
	}
	else
	{
		stepY = -1;
		sideDistX = (1.0 - info->p_x + mapX) * deltaDistY;
	}
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (find_target(info->map, mapX, mapY) != '0')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (mapX - info->p_x + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - info->p_y + (1 - stepY) / 2) / rayDirY;
	// int	lineHeight = (int)(1080 / perpWallDist);
	// int	drawStart = -lineHeight / 2 + 1080 / 2;
	// if (drawStart < 0)
	// 	drawStart = 0;
	// int	drawEnd = lineHeight / 2 + 1080 / 2;
	// if(drawEnd >= 1080)
	// 	drawEnd = 1080 - 1;
	// t_data	*wall = calloc(1, sizeof(t_data));
	// wall->img = mlx_xpm_file_to_image(info->var.mlx, info->no_path, &w, &h);
	// wall->addr = mlx_get_data_addr(wall->img, &wall->bpp, &wall->line_length, &wall->endian);
	// mlx_put_image_to_window(info->var.mlx, info->var.win, wall->img, mapX, mapY);

	int w = 10; int h = 10;
	printf("%d %d\n", start_x, mapY);
	if (side == 1)
	{
		
		void *img = mlx_xpm_file_to_image(info->var.mlx, info->no_path, &w, &h);
		mlx_put_image_to_window(info->var.mlx, info->var.win, img, start_x-32, 508);
	}
	else
	{
		void *img = mlx_xpm_file_to_image(info->var.mlx, info->we_path, &w, &h);
		mlx_put_image_to_window(info->var.mlx, info->var.win, img, start_x-32, 508);
	}
	return (0);
}

int	raycasting(t_info *info)
{
	double	camera_x, rayDirX, rayDirY;
	int		x, w;

	x = 0;
	w = 1920;
	info->dir_x = 0;
	info->dir_y = -1;
	info->plane_x = 0;
	info->plane_y = 0.66;
	while (x < w)
	{
		camera_x = (double)(2 * x) / w - 1;
		rayDirX = info->dir_x + info->plane_x * camera_x;
		rayDirY = info->dir_y + info->plane_y * camera_x;
		dda(info, rayDirX, rayDirY, x);
		x++;
	}
	return (0);
}

int	into_game(t_info *info)
{
	info->var.mlx = mlx_init();
	info->var.win = mlx_new_window(info->var.mlx, 1920, 1080, "cub3d");
	draw_cell_floor(info);
	raycasting(info);
	mlx_hook(info->var.win, PRESS, 0, &key_press, &info->var);
	mlx_hook(info->var.win, RED_BUTTON, 0, &exit_hook, &info->var);
	mlx_loop(info->var.mlx);
	mlx_destroy_window(info->var.mlx, info->var.win);
	return (0);
}
