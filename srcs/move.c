/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:51:43 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/07 16:51:43 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_front(t_info *info)
{
	if (find_target(info->map, \
			(int)(info->p_x + info->dir_x * info->move_speed), \
			(int)info->p_y) != '1')
		info->p_x += info->dir_x * info->move_speed;
	if (find_target(info->map, \
			(int)info->p_x, \
			(int)(info->p_y + info->dir_y * info->move_speed)) != '1')
		info->p_y += info->dir_y * info->move_speed;
}

void	move_back(t_info *info)
{
	if (find_target(info->map, \
			(int)(info->p_x - info->dir_x * info->move_speed), \
			(int)info->p_y) != '1')
		info->p_x -= info->dir_x * info->move_speed;
	if (find_target(info->map, \
			(int)info->p_x, \
			(int)(info->p_y - info->dir_y * info->move_speed)) != '1')
		info->p_y -= info->dir_y * info->move_speed;
}

void	move_right(t_info *info)
{
	if (find_target(info->map, \
			(int)(info->p_x - info->dir_y * info->move_speed), \
			(int)info->p_y) != '1')
		info->p_x += -info->dir_y * info->move_speed;
	if (find_target(info->map, \
			(int)info->p_x, \
			(int)(info->p_y + info->dir_x * info->move_speed)) != '1')
		info->p_y += info->dir_x * info->move_speed;
}

void	move_left(t_info *info)
{
	if (find_target(info->map, \
			(int)(info->p_x + info->dir_y * info->move_speed), \
			(int)info->p_y) != '1')
		info->p_x -= -info->dir_y * info->move_speed;
	if (find_target(info->map, \
			(int)info->p_x, \
			(int)(info->p_y - info->dir_x * info->move_speed)) != '1')
		info->p_y -= info->dir_x * info->move_speed;
}
