/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: littley <littley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:38:03 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 00:03:08 by littley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_wall(t_info *info, t_ray *ray)
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
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - info->p_x + (1 - ray->step_x) / 2)
			/ ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - info->p_y + (1 - ray->step_y) / 2)
			/ ray->dir_y;
}

int	get_texture_num(t_ray *ray)
{
	if (ray->hit == 'C')
		return (4);
	if (ray->side == 0 && ray->dir_x < 0)
		return (0);
	if (ray->side == 0 && ray->dir_x >= 0)
		return (1);
	if (ray->side == 1 && ray->dir_y < 0)
		return (2);
	if (ray->side == 1 && ray->dir_y >= 0)
		return (3);
	return (0);
}

void	init_draw(t_info *info, t_ray *ray, t_draw *draw)
{
	draw->line_height = (int)(W_HEIGHT / ray->perp_wall_dist);
	draw->start = -draw->line_height / 2 + W_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_height / 2 + W_HEIGHT / 2;
	if (draw->end >= W_HEIGHT)
		draw->end = W_HEIGHT - 1;
	draw->tex_num = get_texture_num(ray);
	if (ray->side == 0)
		draw->wall_x = info->p_y + ray->perp_wall_dist * ray->dir_y;
	else
		draw->wall_x = info->p_x + ray->perp_wall_dist * ray->dir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * (double)P_WIDTH);
	if (ray->side == 0 && ray->dir_x > 0)
		draw->tex_x = P_WIDTH - draw->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		draw->tex_x = P_WIDTH - draw->tex_x - 1;
	draw->step = 1.0 * P_HEIGHT / draw->line_height;
	draw->tex_pos = (draw->start - W_HEIGHT / 2 + draw->line_height / 2)
		* draw->step;
}

int	draw_texture_to_img(t_info *info, t_ray *ray, int x)
{
	t_draw	draw;

	ft_memset(&draw, 0, sizeof(t_draw));
	init_draw(info, ray, &draw);
	while (draw.start < draw.end)
	{
		draw.tex_y = (int)draw.tex_pos & (P_HEIGHT - 1);
		draw.tex_pos += draw.step;
		draw.color = info->texture[draw.tex_num]
		[P_HEIGHT * draw.tex_y + draw.tex_x];
		if (ray->side == 1)
			draw.color = (draw.color >> 1) & 8355711;
		info->buff[draw.start][x] = draw.color;
		draw.start++;
	}
	return (0);
}

int	ray_casting(t_info *info, t_ray *ray)
{
	int	x;

	x = -1;
	ft_memset(ray, 0, sizeof(t_ray));
	while (++x < W_WIDTH)
	{
		init_ray(info, ray, x);
		find_wall(info, ray);
		draw_texture_to_img(info, ray, x);
	}
	return (0);
}
