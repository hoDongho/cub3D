/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:52:50 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 15:26:07 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cell_floor(t_info *info, t_img *img)
{
	int	i;
	int	j;
	int	ceiling;
	int	floor;

	ceiling = set_color(info->cub.ceiling);
	floor = set_color(info->cub.floor);
	i = -1;
	while (++i < W_HEIGHT)
	{
		j = -1;
		while (++j < W_WIDTH)
		{
			if (i < W_HEIGHT / 2)
				img->addr[i * W_WIDTH + j] = ceiling;
			if (i >= W_HEIGHT / 2)
				img->addr[i * W_WIDTH + j] = floor;
		}
	}
}

void	draw_game(t_info *info)
{
	int	x;
	int	y;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			if (info->buff[y][x])
			{
				info->main.addr[y * W_WIDTH + x] = info->buff[y][x];
				info->buff[y][x] = 0;
			}
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->main.img, 0, 0);
}
