/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: littley <littley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:46:39 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 00:02:47 by littley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_info_dir(t_info *info)
{
	if (info->start_dir == 'E')
	{
		info->dir_x = 1;
		info->plane_y = 0.99;
	}
	else if (info->start_dir == 'W')
	{
		info->dir_x = -1;
		info->plane_y = -0.99;
	}
	else if (info->start_dir == 'S')
	{
		info->dir_y = 1;
		info->plane_x = -0.99;
	}
	else if (info->start_dir == 'N')
	{
		info->dir_y = -1;
		info->plane_x = 0.99;
	}
}

void	init_step(t_info *info, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (info->p_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - info->p_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (info->p_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - info->p_y) * ray->delta_dist_y;
	}
}

void	init_ray(t_info *info, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)W_WIDTH - 1;
	ray->dir_x = info->dir_x + info->plane_x * ray->camera_x;
	ray->dir_y = info->dir_y + info->plane_y * ray->camera_x;
	ray->map_x = (int)info->p_x;
	ray->map_y = (int)info->p_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	init_step(info, ray);
}
