/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:42:25 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/07 16:50:09 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_hook(t_var *var)
{
	ft_putendl_fd("Bye!", 1);
	mlx_destroy_window(var->mlx, var->win);
	exit(0);
}

void	press_wasd(int keycode, t_info *info)
{
	if (keycode == KEY_W)
		move_front(info);
	else if (keycode == KEY_S)
		move_back(info);
	else if (keycode == KEY_D)
		move_right(info);
	else if (keycode == KEY_A)
		move_left(info);
}

void	press_left_right(int keycode, t_info *info, double rotate)
{
	const double	old_dir_x = info->dir_x;
	const double	old_plane_x = info->plane_x;

	if (keycode == KEY_RIGHT)
	{
		info->dir_x = info->dir_x * cos(rotate) \
						- info->dir_y * sin(rotate);
		info->dir_y = old_dir_x * sin(rotate) \
						+ info->dir_y * cos(rotate);
		info->plane_x = info->plane_x * cos(rotate) \
						- info->plane_y * sin(rotate);
		info->plane_y = old_plane_x * sin(rotate) \
						+ info->plane_y * cos(rotate);
	}
	else if (keycode == KEY_LEFT)
	{
		info->dir_x = info->dir_x * cos(-rotate) \
						- info->dir_y * sin(-rotate);
		info->dir_y = old_dir_x * sin(-rotate) \
						+ info->dir_y * cos(-rotate);
		info->plane_x = info->plane_x * cos(-rotate) \
						- info->plane_y * sin(-rotate);
		info->plane_y = old_plane_x * sin(-rotate) \
						+ info->plane_y * cos(-rotate);
	}
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == KEY_W || keycode == KEY_A \
		|| keycode == KEY_S || keycode == KEY_D)
		press_wasd(keycode, info);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		press_left_right(keycode, info, 0.2);
	else if (keycode == KEY_M && !info->map_sw)
		info->map_sw = 1;
	else if (keycode == KEY_M)
		info->map_sw = 0;
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(info->var.mlx, info->var.win);
		printf("Bye!\n");
		exit(0);
	}
	return (0);
}
