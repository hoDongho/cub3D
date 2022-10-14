/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:53:18 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 15:53:39 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_door(t_dlist *now, int i)
{
	if (now->line[i - 1] == '1' && now->line[i + 1] == '1')
		return (0);
	if (now->next->line[i] == '1' && now->prev->line[i] == '1')
		return (0);
	return (puterr_msg("map error!"));
}

void	change_target(t_info *info, int x, int y)
{
	t_dlist		*tmp;
	static int	door_cnt;
	int			i;

	tmp = info->map;
	i = 0;
	while (tmp->height != y)
		tmp = tmp->next;
	while (i != x)
		i++;
	if (tmp->line[x] == 'c')
		tmp->line[x] = 'O';
	else if (tmp->line[x] == 'C' && info->access_cnt)
	{
		if (door_cnt < info->access_cnt)
			door_cnt++;
		else if (door_cnt == info->access_cnt)
			return ;
		tmp->line[x] = 'O';
	}
	else if (tmp->line[x] == 'O')
		tmp->line[x] = 'c';
}

int	move_door(t_info *info)
{
	if (info->dir_y < 0 && (info->dir_x < 1 || info->dir_x > -1))
		change_target(info, (int)info->p_x, (int)info->p_y - 1);
	else if (info->dir_y > 0 && (info->dir_x < 1 || info->dir_x > -1))
		change_target(info, (int)info->p_x, (int)info->p_y + 1);
	if (info->dir_x < 0 && (info->dir_y < 1 || info->dir_y > -1))
		change_target(info, (int)info->p_x - 1, (int)info->p_y);
	else if (info->dir_x > 0 && (info->dir_y < 1 || info->dir_y > -1))
		change_target(info, (int)info->p_x + 1, (int)info->p_y);
	return (0);
}
