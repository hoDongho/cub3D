/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:38:03 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 16:30:30 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ray_casting.h"

int	find_sprite(t_info *info, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		ray->hit = find_target(info->map, ray->map_x, ray->map_y);
	}
	if (ray->hit == '1' || ray->hit == 'C')
		return (1);
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - info->p_x + (1 - ray->step_x) / 2)
			/ ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - info->p_y + (1 - ray->step_y) / 2)
			/ ray->dir_y;
	return (0);
}

int	draw_sprite_to_img(t_info *info, t_ray *ray, int x)
{
	t_draw	draw;

	ft_memset(&draw, 0, sizeof(t_draw));
	init_draw(info, ray, &draw);
	draw.tex_num = 5 + info->frame_cnt / 10 % 4;
	while (draw.start < draw.end)
	{
		draw.tex_y = (int)draw.tex_pos & (P_HEIGHT - 1);
		draw.tex_pos += draw.step;
		draw.color = info->texture[draw.tex_num]
		[P_HEIGHT * draw.tex_y + draw.tex_x];
		if (draw.color &~ 0xFF000000)
			info->buff[draw.start][x] = draw.color;
		draw.start++;
	}
	return (0);
}

int	sprite_ray_casting(t_info *info)
{
	int		x;
	t_ray	ray;

	x = -1;
	ft_memset(&ray, 0, sizeof(t_ray));
	while (++x < W_WIDTH)
	{
		init_ray(info, &ray, x);
		if (find_sprite(info, &ray))
			continue ;
		draw_sprite_to_img(info, &ray, x);
	}
	return (0);
}
