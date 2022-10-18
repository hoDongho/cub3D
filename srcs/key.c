/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:02:54 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 16:03:02 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_hook(t_info *info)
{
	ft_putendl_fd("Bye!", 1);
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

void	press_move(int keycode, t_info *info)
{
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

void	rotate_view(t_info *info, double rotate)
{
	const double	old_dir_x = info->dir_x;
	const double	old_plane_x = info->plane_x;

	info->dir_x = info->dir_x * cos(rotate) \
					- info->dir_y * sin(rotate);
	info->dir_y = old_dir_x * sin(rotate) \
					+ info->dir_y * cos(rotate);
	info->plane_x = info->plane_x * cos(rotate) \
					- info->plane_y * sin(rotate);
	info->plane_y = old_plane_x * sin(rotate) \
					+ info->plane_y * cos(rotate);
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
		mlx_destroy_window(info->mlx, info->win);
		write(1, "Bye!\n", 5);
		exit(0);
	}
	return (0);
}
