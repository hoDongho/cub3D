/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:42:25 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/05 10:45:58 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_hook(t_var *var)
{
	ft_putendl_fd("Bye!", 1);
	mlx_destroy_window(var->mlx, var->win);
	exit(0);
}

int	key_press(int keycode, t_var *var)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(var->mlx, var->win);
		printf("Bye!\n");
		exit(0);
	}
	return (0);
}