/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:08:00 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/05 10:42:23 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	into_game(t_info *info)
{
	t_var	var;

	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, 1920, 1080, "cub3d");
	mlx_hook(var.win, PRESS, 0, &key_press, &var);
	mlx_hook(var.win, RED_BUTTON, 0, &exit_hook, &var);
	mlx_loop(var.mlx);
	mlx_destroy_window(var.mlx, var.win);
	(void)info;
	return (0);
}
