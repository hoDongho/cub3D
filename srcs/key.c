/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:42:25 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/07 13:33:38 by yehyun           ###   ########seoul.kr  */
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
	{
		if (find_target(info->map, (int)(info->p_x + info->dir_x * info->move_speed), (int)info->p_y) != '1')
			info->p_x += info->dir_x * info->move_speed;
		if (find_target(info->map, (int)info->p_x, (int)(info->p_y + info->dir_y * info->move_speed)) != '1')
			info->p_y += info->dir_y * info->move_speed;
		printf("x : %f, y : %f\n", info->p_x, info->p_y);
	}
	else if (keycode == KEY_S)
	{
		if (find_target(info->map, (int)(info->p_x - info->dir_x * info->move_speed), (int)info->p_y) != '1') //0 + 1.2 1.2 // 23.8
			info->p_x -= info->dir_x * info->move_speed;
		if (find_target(info->map, (int)info->p_x, (int)(info->p_y - info->dir_y * info->move_speed)) != '1')
			info->p_y -= info->dir_y * info->move_speed;
		printf("x : %f, y : %f\n", info->p_x, info->p_y);
	}
	else if (keycode == KEY_D)
	{
		if (find_target(info->map, (int)(info->p_x - info->dir_y * info->move_speed), (int)info->p_y) != '1')
			info->p_x += -info->dir_y * info->move_speed;
		if (find_target(info->map, (int)info->p_x, (int)(info->p_y + info->dir_x * info->move_speed)) != '1')
			info->p_y += info->dir_x * info->move_speed;
		printf("x : %f, y : %f\n", info->p_x, info->p_y);
	}
	else if (keycode == KEY_A)
	{
		if (find_target(info->map, (int)(info->p_x + info->dir_y * info->move_speed), (int)info->p_y) != '1')
			info->p_x -= -info->dir_y * info->move_speed;
		if (find_target(info->map, (int)info->p_x, (int)(info->p_y - info->dir_x * info->move_speed)) != '1')
			info->p_y -= info->dir_x * info->move_speed;
		printf("x : %f, y : %f\n", info->p_x, info->p_y);
	}
}

void	press_left_right(int keycode, t_info *info)
{
	const double	old_dir_x = info->dir_x;
	const double	old_plane_x = info->plane_x;

	if (keycode == KEY_RIGHT)
	{
		info->dir_x = info->dir_x * cos(info->rotate) - info->dir_y * sin(info->rotate);
		info->dir_y = old_dir_x * sin(info->rotate) + info->dir_y * cos(info->rotate);
		info->plane_x = info->plane_x * cos(info->rotate) - info->plane_y * sin(info->rotate);
		info->plane_y = old_plane_x * sin(info->rotate) + info->plane_y * cos(info->rotate);
	}
	else if (keycode == KEY_LEFT)
	{
		info->dir_x = info->dir_x * cos(-info->rotate) - info->dir_y * sin(-info->rotate);
		info->dir_y = old_dir_x * sin(-info->rotate) + info->dir_y * cos(-info->rotate);
		info->plane_x = info->plane_x * cos(-info->rotate) - info->plane_y * sin(-info->rotate);
		info->plane_y = old_plane_x * sin(-info->rotate) + info->plane_y * cos(-info->rotate);	
	}
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		press_wasd(keycode, info);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		press_left_right(keycode, info);
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(info->var.mlx, info->var.win);
		printf("Bye!\n");
		exit(0);
	}
	return (0);
}
