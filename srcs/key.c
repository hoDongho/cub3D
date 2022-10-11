/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:42:25 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/11 16:12:37 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_hook(t_var *var)
{
	ft_putendl_fd("Bye!", 1);
	mlx_destroy_window(var->mlx, var->win);
	exit(0);
}

void	press_move(int keycode, t_info *info)
{
	printf("x: %f y: %f\n", info->dir_x, info->dir_y);
	if (keycode == KEY_W)
		info->key_flag[0] = 1;
	else if (keycode == KEY_S)
		info->key_flag[1] = 1;
	else if (keycode == KEY_D)
		info->key_flag[2] = 1;
	else if (keycode == KEY_A)
		info->key_flag[3] = 1;
	else if (keycode == KEY_LEFT)
		info->key_flag[4] = 1;
	else if (keycode == KEY_RIGHT)
		info->key_flag[5] = 1;
}

void	rotate_view(int keycode, t_info *info, double rotate)
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

int	key_release(int keycode, t_info *info)
{
	if (keycode == KEY_W)
		info->key_flag[0] = 0;
	else if (keycode == KEY_S)
		info->key_flag[1] = 0;
	else if (keycode == KEY_D)
		info->key_flag[2] = 0;
	else if (keycode == KEY_A)
		info->key_flag[3] = 0;
	else if (keycode == KEY_LEFT)
		info->key_flag[4] = 0;
	else if (keycode == KEY_RIGHT)
		info->key_flag[5] = 0;
	return (0);
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_LEFT \
		|| keycode == KEY_S || keycode == KEY_D || keycode == KEY_RIGHT)
		press_move(keycode, info);
	else if (keycode == KEY_M && !info->map_sw)
		info->map_sw = 1;
	else if (keycode == KEY_M)
		info->map_sw = 0;
	else if (keycode == KEY_SPACE)
		move_door(info);
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(info->var.mlx, info->var.win);
		printf("Bye!\n");
		exit(0);
	}
	return (0);
}
