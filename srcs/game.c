/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:08:00 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/06 16:49:18 by yehyun           ###   ########seoul.kr  */
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
	printf("%d, %d\n", ceiling, floor);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if (i < HEIGHT / 2)
				img->addr[i * WIDTH + j] = ceiling;
			if (i >= HEIGHT / 2)
				img->addr[i * WIDTH + j] = floor;
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

void	set_texture(t_info *info)
{
	int		i;
	t_img	img;

	i = -1;
	while (++i < 4)
		info->texture[i] = ft_calloc(P_HEIGHT * P_WIDTH, sizeof(int));
	load_image(info, info->texture[0], info->ea_path, &img);
	load_image(info, info->texture[1], info->we_path, &img);
	load_image(info, info->texture[2], info->so_path, &img);
	load_image(info, info->texture[3], info->no_path, &img);
}

void	draw_game(t_info *info, int **buff)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (buff[y][x])
			{
				info->main.addr[y * WIDTH + x] = buff[y][x];
				buff[y][x] = 0;
			}
		}
	}
}

int	into_game(t_info *info)
{
	int	**buff;
	int	i;

	i = -1;
	buff = ft_calloc(HEIGHT, sizeof(int *));
	while (++i < HEIGHT)
		buff[i] = ft_calloc(WIDTH, sizeof(int));
	info->var.mlx = mlx_init();
	info->var.win = mlx_new_window(info->var.mlx, WIDTH, HEIGHT, "cub3d");
	info->main.img = mlx_new_image(info->var.mlx, WIDTH, HEIGHT);
	info->main.addr = (int *)mlx_get_data_addr(info->main.img, &info->main.bpp,
			&info->main.line_length, &info->main.endian);
	info->texture = ft_calloc(4, sizeof(int *));
	draw_cell_floor(info, &info->main);
	set_texture(info);
	ray_casting(info, &info->ray, buff);
	draw_game(info, buff);
	mlx_put_image_to_window(info->var.mlx, info->var.win, info->main.img, 0, 0);
	mlx_hook(info->var.win, PRESS, 0, &key_press, &info->var);
	mlx_hook(info->var.win, RED_BUTTON, 0, &exit_hook, &info->var);
	mlx_loop(info->var.mlx);
	return (0);
}
