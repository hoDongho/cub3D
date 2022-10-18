/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:51:43 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/18 13:07:21 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	key_move(t_info *info)
{
	if (info->key_flag[0])
		move_front(info);
	if (info->key_flag[1])
		move_back(info);
	if (info->key_flag[2])
		move_right(info);
	if (info->key_flag[3])
		move_left(info);
	if (info->key_flag[4])
		rotate_view(info, -ROTATE_SPEED);
	if (info->key_flag[5])
		rotate_view(info, ROTATE_SPEED);
}
