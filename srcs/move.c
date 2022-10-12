/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:51:43 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/12 11:52:39 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	test(double p)
{
	return (p - (int)p);
}

void	move_front(t_info *info)
{
	if (find_target(info->map, \
			(int)(info->p_x + info->dir_x * MOVE_SPEED * 4), \
			(int)info->p_y) <= 0)
		info->p_x += info->dir_x * MOVE_SPEED;
	if (find_target(info->map, \
			(int)info->p_x, \
			(int)(info->p_y + info->dir_y * MOVE_SPEED * 4)) <= 0)
		info->p_y += info->dir_y * MOVE_SPEED;
}

void	move_back(t_info *info)
{
	if (find_target(info->map, \
			(int)(info->p_x - info->dir_x * MOVE_SPEED * 4), \
			(int)info->p_y) <= 0)
		info->p_x -= info->dir_x * MOVE_SPEED;
	if (find_target(info->map, \
			(int)info->p_x, \
			(int)(info->p_y - info->dir_y * MOVE_SPEED * 4)) <= 0)
		info->p_y -= info->dir_y * MOVE_SPEED;
}

void	move_right(t_info *info)
{
	if (find_target(info->map, \
			(int)(info->p_x - info->dir_y * MOVE_SPEED * 4), \
			(int)info->p_y) <= 0)
		info->p_x += -info->dir_y * MOVE_SPEED;
	if (find_target(info->map, \
			(int)info->p_x, \
			(int)(info->p_y + info->dir_x * MOVE_SPEED * 4)) <= 0)
		info->p_y += info->dir_x * MOVE_SPEED;
}

void	move_left(t_info *info)
{
	if (find_target(info->map, \
			(int)(info->p_x + info->dir_y * MOVE_SPEED * 4), \
			(int)info->p_y) <= 0)
		info->p_x -= -info->dir_y * MOVE_SPEED;
	if (find_target(info->map, \
			(int)info->p_x, \
			(int)(info->p_y - info->dir_x * MOVE_SPEED * 4)) <= 0)
		info->p_y -= info->dir_x * MOVE_SPEED;
}
