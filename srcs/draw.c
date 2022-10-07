/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:52:50 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/07 16:54:01 by yehyun           ###   ########seoul.kr  */
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
